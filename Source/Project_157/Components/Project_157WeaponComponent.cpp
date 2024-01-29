// Copyright (c) 2024 @ Rafael Zagolin
#include "Project_157WeaponComponent.h"

#include "Project_157/Characters/Project_157Player.h"


#include "DrawDebugHelpers.h"



#define HIGH_NUMBER 10000000.f


// Sets default values for this component's properties
UProject_157WeaponComponent::UProject_157WeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CollisionChannel = ECC_Visibility;
}

// Called when the game starts
void UProject_157WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	WeaponCodeData.CurrentAmmo = WeaponCodeData.MaxAmmoPerClip;
}

// Called every frame
void UProject_157WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UProject_157WeaponComponent::Start_UsingItem()
{
	Super::Start_UsingItem();

	//UE_LOG(Log_Project_157ItemComponent, Display, TEXT("%s"), *FString(__FUNCTION__));
	
	IProject_157CharacterInterface* CharacterInterface = Cast<IProject_157CharacterInterface>(GetOwner());
	if(!CharacterInterface)
	{
		return;
	}
	CharacterInterface->SetCurrentState_Implementation(EProject_157ActionState::Shooting);
	

	StartShooting();
}

void UProject_157WeaponComponent::Stop_UsingItem()
{
	Super::Stop_UsingItem();
	
	IProject_157CharacterInterface* CharacterInterface = Cast<IProject_157CharacterInterface>(GetOwner());
	if(!CharacterInterface)
	{
		return;
	}

	CharacterInterface->ResetState_Implementation(EProject_157ActionState::Shooting);	

	StopShooting();
	
	GetWorld()->GetTimerManager().SetTimer(WasShootingTimer, [this]()
	{
	}, WasShootingTimerF, false);
}

void UProject_157WeaponComponent::AddingExistingItem()
{
	Super::AddingExistingItem();
	
	// for now I'm hard coding the bullets amount that will get added to this weapon
	WeaponCodeData.TotalRemainingAmmo  += WeaponCodeData.MaxAmmoPerClip * WeaponCodeData.ClipsAmountToCollect;
	//UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
}


void UProject_157WeaponComponent::StartShooting()
{
	//UE_LOG(LogCS_WeaponComponent, Display, TEXT(""));
	
	GetWorld()->GetTimerManager().SetTimer(
		WeaponCodeData.FireRateTimer,
		[&]()
		{
			Shoot();
		},
		WeaponCodeData.FireRate,
		WeaponCodeData.WeaponFireType == EProject_157WeaponFireType::Automatic ? true : false,
		0.f);
}

void UProject_157WeaponComponent::StopShooting()
{
	//UE_LOG(LogCS_WeaponComponent, Display, TEXT("%s"), *FString(__FUNCTION__));
	GetWorld()->GetTimerManager().ClearTimer(WeaponCodeData.FireRateTimer);
}

void UProject_157WeaponComponent::Shoot()
{
	//UE_LOG(LogCS_WeaponComponent, Display, TEXT("%s"), *FString(__FUNCTION__));
	PlayShootSound();
	
	if (WeaponCodeData.bInfiniteBullets)
	{
		Hitscan();
		return;
	}

	if (WeaponCodeData.CurrentAmmo - 1 > 0)
	{
		WeaponCodeData.CurrentAmmo--;

		// TODO: Check to see why it's not working with ternary operator
		//WeaponData.bHitscan ?  Hitscan() : SpawnProjectile();
		Hitscan();		
		return;
	}
	WeaponCodeData.CurrentAmmo = 0;
}

void UProject_157WeaponComponent::Hitscan()
{
	//UE_LOG(LogCS_WeaponComponent, Display, TEXT("%s"), *FString(__FUNCTION__));

	// Camera line trace
	FVector MuzzleLoc = FVector::ZeroVector;
	const FVector EndLoc = CameraTrace_Helper().bBlockingHit ? CameraTrace_Helper().ImpactPoint : CameraTrace_Helper().TraceEnd;
	
	
	IProject_157CharacterInterface* heroInterface = Cast<IProject_157CharacterInterface>(GetOwner());
	if (heroInterface)
	{
		IProject_157CharacterInterface::Execute_OnShoot(GetOwner(), MuzzleLoc);
	}
	
	FVector Dir = MuzzleLoc +  FRotationMatrix::MakeFromX(EndLoc - MuzzleLoc).GetUnitAxis(EAxis::X) * WeaponCodeData.BulletRange;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLoc, Dir, CollisionChannel);
	//UE_LOG(LogTemp, Display, TEXT("%s"), *HitResult.Actor->GetName());
	
	if(WeaponCodeData.bDebug)
	{
		DrawDebugLine(GetWorld(), MuzzleLoc, Dir, WeaponCodeData.Debug_Color, WeaponCodeData.Debug_Persistent,
			WeaponCodeData.Debug_LifeTime, 0, WeaponCodeData.Debug_Thickness);

		DrawDebugPoint(GetWorld(), HitResult.Location, 5.f, FColor::Red, WeaponCodeData.Debug_Persistent, WeaponCodeData.Debug_LifeTime + 6.f);
	}
	// Debug hit bone
	// if(HitResult.BoneName != "None")
	// 	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(HitResult.BoneName.ToString()));
	//
	if(HitResult.bBlockingHit)
	{
		AActor* hitActor = HitResult.GetActor();
		if(!hitActor)
		{
			return;
		}
		
		IProject_157CharacterInterface* CharacterInterface = Cast<IProject_157CharacterInterface>(hitActor);		
		if(!CharacterInterface)
			return;

		// Call character interface to damage pawn
		CharacterInterface->TakeDamage_Implementation(WeaponCodeData.Damage, FDamageEvent(), nullptr, GetOwner(), HitResult.BoneName);		
	}
}

void UProject_157WeaponComponent::TryReload()
{
	// Reload weapon
	if(WeaponCodeData.CurrentAmmo == WeaponCodeData.MaxAmmoPerClip)
	{
		UE_LOG(Log_Project_157ItemComponent, Display, TEXT("%s, No need to reload"), *FString(__FUNCTION__));
		return;
	}
	
	if(WeaponCodeData.TotalRemainingAmmo > 0)
	{
		// find how many bullets we need
		int32 x = WeaponCodeData.MaxAmmoPerClip - WeaponCodeData.CurrentAmmo;
		PlayReloadSound();
		if(WeaponCodeData.TotalRemainingAmmo >= x)
		{
			WeaponCodeData.TotalRemainingAmmo -= x;
		}
		else
		{
			x = WeaponCodeData.TotalRemainingAmmo;
			WeaponCodeData.TotalRemainingAmmo = 0;
		}
		WeaponCodeData.CurrentAmmo += x;
		UE_LOG(Log_Project_157ItemComponent, Display, TEXT("%s, reloading"), *FString(__FUNCTION__));
	}
	else
	{
		UE_LOG(Log_Project_157ItemComponent, Display, TEXT("%s, No ammo left to reload"), *FString(__FUNCTION__));
	}
}

void UProject_157WeaponComponent::SpawnProjectile()
{
	//UE_LOG(LogCS_WeaponComponent, Display, TEXT("%s"), *FString(__FUNCTION__));
}

FHitResult UProject_157WeaponComponent::CameraTrace_Helper()
{
	// Camera line trace
	FVector MuzzleLoc = FVector::ZeroVector;
	FVector Dir = FVector::ZeroVector;
	
	IProject_157CharacterInterface* heroInterface = Cast<IProject_157CharacterInterface>(GetOwner());	
	if (heroInterface)
	{
		
		heroInterface->OnShoot_Camera_Implementation(MuzzleLoc, Dir);
	}
	
	Dir = MuzzleLoc + Dir * HIGH_NUMBER;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLoc, Dir, CollisionChannel);
	//UE_LOG(Log_Project_157ItemComponent, Display, TEXT("%s"), *HitResult.Actor->GetName());
	return HitResult;
}