// Copyright (c) 2024 @ Rafael Zagolin

#include "Project_157Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"



#include "TimerManager.h"
#include "Project_157/Components/Project_157HealthComponent.h"
#include "Project_157/Components/Project_157InventoryComponent.h"
#include "Project_157/Components/Project_157ItemComponent.h"
#include "Project_157/Components/Project_157WeaponComponent.h"
#include "Project_157/Interfaces/Project_157ItemInterface.h"

DEFINE_LOG_CATEGORY(LogProject_157Player);


// Sets default values
AProject_157Player::AProject_157Player(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Creating spring arm component by default */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	if (SpringArmComponent)
	{
		SpringArmComponent->SetupAttachment(RootComponent);
		SpringArmComponent->bUsePawnControlRotation = true;
	}

	/* Creating camera component by default */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	if (CameraComponent)
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
	}

	/* Creating inventory component by default */
	InventoryComponent = CreateDefaultSubobject<UProject_157InventoryComponent>(TEXT("Inventory Component"));
	
	/* Creating inventory component by default */
	HealthComponent = CreateDefaultSubobject<UProject_157HealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(100);
	
	
	// Default params for character
	// Keep character facing forward (to where camera is facing)
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	
}

bool AProject_157Player::CheckState(EProject_157ActionState stateToCheck)
{
	// check if that particular bit is on or not
	return (CurrentActionState & static_cast<uint32>(stateToCheck) ) > (static_cast<uint32>(stateToCheck) - 1);
}

void AProject_157Player::SetCurrentState(EProject_157ActionState state)
{
	// turn on that particular bit
	CurrentActionState |= static_cast<uint32>(state);
}

void AProject_157Player::ResetState(EProject_157ActionState state)
{
	// turn off that particular bit
	CurrentActionState &= (~static_cast<uint32>(state));
}


// Called when the game starts or when spawned
void AProject_157Player::BeginPlay()
{
	Super::BeginPlay();

}

void AProject_157Player::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AProject_157Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void AProject_157Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::Input_MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::Input_MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ThisClass::Input_LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::Input_LookUp);

	// Weapon actions
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ThisClass::Input_Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ThisClass::Input_Shoot);
	
}


float AProject_157Player::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator,
                            AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void AProject_157Player::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(!OtherActor)
	{
		return;
	}
	
	if(IProject_157ItemInterface* itemInterface = Cast<IProject_157ItemInterface>(OtherActor))
	{
		IProject_157ItemInterface::Execute_PickupItem(OtherActor, this);	
	}
}


#pragma region Input 

void AProject_157Player::Input_MoveForward(float Axis)
{
	if(Axis == 0.f)
		return;
	
	const FRotator controlRotation = FRotator(0.F,GetControlRotation().Yaw, 0.F);	
	const FVector DesiredDirection = FRotationMatrix(controlRotation).GetUnitAxis(EAxis::X);
	
	// the coolest way to deference a pointer
	(*this).AddMovementInput(DesiredDirection, Axis);
}

void AProject_157Player::Input_MoveRight(float Axis)
{
	if(Axis == 0.f)
		return;
	
	const FRotator controlRotation = FRotator(0.F,GetControlRotation().Yaw, 0.F);	
	const FVector DesiredDirection = FRotationMatrix(controlRotation).GetUnitAxis(EAxis::Y);
	
	// the coolest way to deference a pointer
	(*this).AddMovementInput(DesiredDirection, Axis);
}

void AProject_157Player::Input_LookUp(float Axis)
{	
	if(Axis == 0.f)
		return;

	// TODO: Multiply axis by a sensitivity 
	AddControllerPitchInput(Axis);
}

void AProject_157Player::Input_LookRight(float Axis)
{	
	if(Axis == 0.f)
		return;
	
	// TODO: Multiply axis by a sensitivity
	AddControllerYawInput(Axis);
}

void AProject_157Player::Input_Jump()
{
	this->Jump();
}

void AProject_157Player::Input_Sprint()
{
	// TODO:
}

void AProject_157Player::Input_Shoot()
{
	// TODO:
	UE_LOG(LogProject_157Player, Display, TEXT("%s"), *FString(__FUNCTION__));

	check(InventoryComponent);

	UProject_157ItemComponent* CurrentItem = InventoryComponent->GetCurrentItem();
	if (!CurrentItem)
	{
		//UE_LOG(LogProject_157Player, Warning, TEXT("No current item"));
		return;
	}

	CurrentItem->IsUsingItem() ? CurrentItem->Stop_UsingItem() : CurrentItem->Start_UsingItem();
}

void AProject_157Player::Input_Reload()
{
	// Let's do this assertion check since the inventory component has to be on the player at all times
	check(InventoryComponent);

	// Check if we are equipped with an item at all
	if (!InventoryComponent->GetCurrentItem())
	{
		UE_LOG(LogProject_157Player, Display, TEXT("%s, invalid current item!"), *FString(__FUNCTION__));
		return;
	}

	// Check if we are equipped with a weapon	
	UProject_157WeaponComponent* currentEquippedWeapon = Cast<UProject_157WeaponComponent>(InventoryComponent->GetCurrentItem());
	if (!currentEquippedWeapon)
	{
		UE_LOG(LogProject_157Player, Display, TEXT("%s, invalid currentEquippedWeapon!"), *FString(__FUNCTION__));
		return;
	}

	currentEquippedWeapon->TryReload();
}

void AProject_157Player::Input_ItemCycleUp()
{
	// TODO:
}

void AProject_157Player::Input_ItemCycleDown()
{
	// TODO:
}

void AProject_157Player::Input_Aim()
{
	// TODO:
}


#pragma endregion

#pragma region IProject_157CharacterInterface 

void AProject_157Player::OnChangeInventoryItem_Implementation()
{
	IProject_157CharacterInterface::OnChangeInventoryItem_Implementation();
}

// Blueprint will be overriding this method
void AProject_157Player::OnShoot_Implementation(FVector& _MuzzleLocation)
{
	IProject_157CharacterInterface::OnShoot_Implementation(_MuzzleLocation);
}

void AProject_157Player::OnShoot_Camera_Implementation(FVector& _MuzzleLocation, FVector& Direction)
{
	IProject_157CharacterInterface::OnShoot_Camera_Implementation(_MuzzleLocation, Direction);

	check(CameraComponent);

	_MuzzleLocation = CameraComponent->GetComponentLocation();
	Direction = CameraComponent->GetForwardVector();
}

void AProject_157Player::TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	IProject_157CharacterInterface::TakeDamage_Implementation(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// TODO: Filter damage
	this->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}

void AProject_157Player::AddItem_Implementation(TSubclassOf<UProject_157ItemComponent> ItemToAdd)
{
	IProject_157CharacterInterface::AddItem_Implementation(ItemToAdd);
	
	// Add item
	UProject_157ItemComponent* item = Cast<UProject_157ItemComponent>(AddComponentByClass(ItemToAdd, false, GetTransform(), true));
	if (item)
	{
		item->RegisterComponent();
		InventoryComponent->AddToInventory(item);
		UE_LOG(LogProject_157Player, Display, TEXT("%s"), *FString(__FUNCTION__));
	}
}

#pragma endregion 
