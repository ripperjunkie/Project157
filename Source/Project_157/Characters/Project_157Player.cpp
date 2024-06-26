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
#include "Project_157/Components/Project_157AimComponent.h"
#include "Project_157/Components/Project_157SprintComponent.h"

#include "Project_157/DebugTools/DebugImGui.h"


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

	/* Creating sprint component by default */
	SprintComponent = CreateDefaultSubobject<UProject_157SprintComponent>(TEXT("SprintComponent"));
		
	/* Creating aim component by default */
	AimComponent = CreateDefaultSubobject<UProject_157AimComponent>(TEXT("AimComponent"));

	
	WeaponSKComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSK"));
	WeaponSKComponent->SetupAttachment(GetRootComponent());

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


// Called when the game starts or when spawned
void AProject_157Player::BeginPlay()
{
	Super::BeginPlay();

#if UE_BUILD_DEVELOPMENT || UE_EDITOR || UE_BUILD_DEBUG
	Debug_ImGui = new DebugImGui();
#endif
	
	check(SprintComponent);
	check(AimComponent);

	PlayerData.DefaultFOV = CameraComponent->FieldOfView;
	PlayerData.DefaultArmLength = SpringArmComponent->TargetArmLength;
	DefaultMovementSettings.MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SprintComponent->PlayerRef = this;
	AimComponent->PlayerRef = this;
}


void AProject_157Player::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#if UE_BUILD_DEVELOPMENT || UE_EDITOR || UE_BUILD_DEBUG
	delete Debug_ImGui;
#endif

	
}

// Called every frame
void AProject_157Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CheckState_Implementation(EProject_157ActionState::Sprinting))
	{
		if(GetCharacterMovement()->GetCurrentAcceleration().Size() == 0)
		{
			// it means player is not giving input to keep moving character
			if(!CheckState_Implementation(EProject_157ActionState::Crouching) || !CheckState_Implementation(EProject_157ActionState::Aiming))
				SprintComponent->StopSprint();
			
			ResetState_Implementation(EProject_157ActionState::Sprinting);			
		}
	}

#if UE_BUILD_DEVELOPMENT || UE_EDITOR || UE_BUILD_DEBUG
	if(Debug_ImGui)
	{
		Debug_ImGui->DrawInfo(this);
	}
#endif

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

	// Traversal actions
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ThisClass::Input_Sprint);

	// Weapon actions
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ThisClass::Input_StartShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ThisClass::Input_StopShoot);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, AimComponent, &UProject_157AimComponent::StartAim);	
	PlayerInputComponent->BindAction("Aim", IE_Released, AimComponent,  &UProject_157AimComponent::StopAim);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ThisClass::Input_Reload);
	PlayerInputComponent->BindAction("ItemCycleUp", IE_Pressed, this, &ThisClass::Input_ItemCycleUp);
	PlayerInputComponent->BindAction("ItemCycleDown", IE_Pressed, this, &ThisClass::Input_ItemCycleDown);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ThisClass::Input_ToggleCrouch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Input_Jump);
	
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

	// Check to see if overlapped item implements interface, if so, call it on the object.
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
	UE_LOG(LogProject_157Player, Display, TEXT("%s"), *FString(__FUNCTION__));	
	check(SprintComponent);
	
	if(!CheckState_Implementation(EProject_157ActionState::Sprinting))
	{
		SprintComponent->StartSprint();
		return;
	}
	SprintComponent->StopSprint();
}

void AProject_157Player::Input_ToggleCrouch()
{
	// Set character to crouch mode	
	if (!CheckState_Implementation(EProject_157ActionState::Crouching) && GetCharacterMovement()->IsMovingOnGround())
	{
		GetCharacterMovement()->Crouch();
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.CrouchWalkSpeed;
		SetCurrentState_Implementation(EProject_157ActionState::Crouching);
		ResetState_Implementation(EProject_157ActionState::Sprinting);
		return;
	}

	// Reset character from crouch mode
	GetCharacterMovement()->UnCrouch();
	ResetState_Implementation(EProject_157ActionState::Crouching);

	if (!CheckState_Implementation(EProject_157ActionState::Aiming))
		GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSettings.MaxWalkSpeed;

}

void AProject_157Player::Input_StartShoot()
{
	//UE_LOG(LogProject_157Player, Display, TEXT("%s"), *FString(__FUNCTION__));

	check(InventoryComponent);

	UProject_157ItemComponent* CurrentItem = InventoryComponent->GetCurrentItem();
	if (!CurrentItem)
	{
		//UE_LOG(LogProject_157Player, Warning, TEXT("No current item"));
		return;
	}

	CurrentItem->Start_UsingItem();
}

void AProject_157Player::Input_StopShoot()
{
	check(InventoryComponent);

	UProject_157ItemComponent* CurrentItem = InventoryComponent->GetCurrentItem();
	if (!CurrentItem)
	{
		//UE_LOG(LogProject_157Player, Warning, TEXT("No current item"));
		return;
	}

	CurrentItem->Stop_UsingItem();
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
	
	Input_ReloadBP();
	currentEquippedWeapon->TryReload();
}

void AProject_157Player::Input_ItemCycleUp()
{
	check(InventoryComponent);
	InventoryComponent->StopUsingItemRequest();
	InventoryComponent->CycleUp();
}

void AProject_157Player::Input_ItemCycleDown()
{
	check(InventoryComponent);
	InventoryComponent->StopUsingItemRequest();
	InventoryComponent->CycleDown();
}


#pragma endregion

#pragma region IProject_157CharacterInterface 

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

void AProject_157Player::TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FName BoneName)
{
	IProject_157CharacterInterface::TakeDamage_Implementation(DamageAmount, DamageEvent, EventInstigator, DamageCauser, BoneName);

	// TODO: Filter damage
	this->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}

void AProject_157Player::AddItem_Implementation(TSubclassOf<UProject_157ItemComponent> ItemToAdd)
{
	IProject_157CharacterInterface::AddItem_Implementation(ItemToAdd);
	
	// Add item to player inventory
	UProject_157ItemComponent* item = Cast<UProject_157ItemComponent>(AddComponentByClass(ItemToAdd, false, GetTransform(), true));
	if (item)
	{
		item->RegisterComponent();
		InventoryComponent->AddToInventory(item);
		UE_LOG(LogProject_157Player, Display, TEXT("%s"), *FString(__FUNCTION__));
	}
}

void AProject_157Player::OnChangeInventoryItem_Implementation()
{
	/* This wouldn't be the final code, we'd have to iterate on it based on different items types.
	 * Currently we only have weapon item type so it's fine.
	*/
	const UProject_157WeaponComponent* WeaponItem =  Cast<UProject_157WeaponComponent>(InventoryComponent->GetCurrentItem());
	
	if(!WeaponItem)
	{
		SetCurrentEquippedWeaponType(EProject_157Weapon::None);
		ResetState_Implementation(EProject_157ActionState::ItemEquipped);
		return;
	}
		
	SetCurrentState_Implementation(EProject_157ActionState::ItemEquipped);
	SetCurrentEquippedWeaponType(WeaponItem->WeaponCodeData.Weapon);
}

float AProject_157Player::GetGroundSpeed_Implementation()
{
	 	float Speed = 0;	
	 	const FVector velocity = GetCharacterMovement()->Velocity;
	 	Speed = FVector(velocity.X, velocity.Y,0.F).Size();
	 	return Speed;
}

EProject_157ActionState AProject_157Player::GetCharacterState_Implementation()
{
	
	return static_cast<EProject_157ActionState>(FMath::Log2(CurrentActionState));
}

EProject_157Weapon AProject_157Player::GetCurrentEquippedWeapon_Implementation()
{
	return static_cast<EProject_157Weapon>(FMath::Log2(CurrentEquippedWeapon));
}

bool AProject_157Player::GetCheckState_Implementation(EProject_157ActionState State)
{
	return this->CheckState_Implementation(State);
}

float AProject_157Player::GetLookForwardAngle_Implementation()
{
	FVector actorRight = GetActorRightVector().GetSafeNormal();
	FVector controlDirection = FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::X).GetSafeNormal();

	float forwardAngle =   FVector::DotProduct(actorRight, controlDirection)	/ (actorRight.Size() * controlDirection.Size());
	forwardAngle = RAD_TO_DEG(FMath::Acos(forwardAngle));
	return forwardAngle - 90.F;
}

float AProject_157Player::GetLookUpAngle_Implementation()
{
	FVector actorUp = GetActorUpVector().GetSafeNormal();
	FVector controlDirection = FRotationMatrix(FRotator(GetControlRotation().Pitch, 0, 0)).GetUnitAxis(EAxis::X).GetSafeNormal();
	
	float upAngle = FVector::DotProduct(actorUp, controlDirection) / (actorUp.Size() * controlDirection.Size());
	upAngle = RAD_TO_DEG(FMath::Acos(upAngle));
	return upAngle - 90.f;
}

void AProject_157Player::OnEnteredVehicle()
{
	if (AimComponent)
		AimComponent->StopAim();
	
	if (Debug_GetWeaponComponent())
	{
		Debug_GetWeaponComponent()->StopShooting();
	}

	// Reset character from crouch mode
	if (CheckState_Implementation(EProject_157ActionState::Crouching))
	{
		GetCharacterMovement()->UnCrouch();
		ResetState_Implementation(EProject_157ActionState::Crouching);

		if (!CheckState_Implementation(EProject_157ActionState::Aiming))
			GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSettings.MaxWalkSpeed;
	}

	if (SprintComponent)
		SprintComponent->StopSprint();
}

void AProject_157Player::OnExitedVehicle()
{

}

#pragma endregion

#pragma region IProject_157DebugInfo

UProject_157WeaponComponent* AProject_157Player::Debug_GetWeaponComponent() const
{
	UProject_157WeaponComponent* weaponComp = Cast<UProject_157WeaponComponent>(InventoryComponent->GetCurrentItem());
	if(weaponComp)
	{
		return weaponComp;
	}
	return nullptr;	
}

#pragma endregion

bool AProject_157Player::CheckState_Implementation(EProject_157ActionState stateToCheck)
{
	// check if that particular bit is on or not
	return (CurrentActionState & static_cast<uint32>(stateToCheck) ) > (static_cast<uint32>(stateToCheck) - 1);
}

void AProject_157Player::SetCurrentState_Implementation(EProject_157ActionState state)
{
	// turn on that particular bit
	CurrentActionState |= static_cast<uint32>(state);
}

void AProject_157Player::ResetState_Implementation(EProject_157ActionState state)
{
	// turn off that particular bit
	CurrentActionState &= (~static_cast<uint32>(state));
}

bool AProject_157Player::CheckEquippedWeapon(EProject_157Weapon EquippedWeapon)
{
	return (CurrentEquippedWeapon & static_cast<uint32>(EquippedWeapon) ) > (static_cast<uint32>(EquippedWeapon) - 1);
}
			
void AProject_157Player::SetCurrentEquippedWeaponType(EProject_157Weapon state)
{	
	CurrentEquippedWeapon |= static_cast<uint32>(state);
}

void AProject_157Player::ResetCurrentEquippedWeaponState(EProject_157Weapon state)
{
	CurrentEquippedWeapon &= (~static_cast<uint32>(state));
}

