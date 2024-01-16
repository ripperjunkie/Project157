// Copyright (c) 2023 @ Rafael Zagolin


#include "Project_157Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"

#include "Project_157/Components/Project_157EnterExitVehicleComponent.h"


#include "TimerManager.h"

DEFINE_LOG_CATEGORY(Log_Player);


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

	/* Creating enter exit vehicle component */
	EnterExitVehicleComponent = CreateDefaultSubobject<UProject_157EnterExitVehicleComponent>(TEXT("EnterExitVehicle Component"));

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
	
	
}


float AProject_157Player::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator,
                            AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

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
