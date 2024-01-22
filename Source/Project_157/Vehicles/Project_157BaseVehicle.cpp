// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_157BaseVehicle.h"

#include "Components/Project_157WheelFront.h"
#include "Components/Project_157WheelRear.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetSystemLibrary.h"

const FName AProject_157BaseVehicle::LookUpBinding("LookUp");
const FName AProject_157BaseVehicle::LookRightBinding("LookRight");

#define LOCTEXT_NAMESPACE "VehiclePawn"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

AProject_157BaseVehicle::AProject_157BaseVehicle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	L_HeadlightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("L_HeadlightComp"));
	L_HeadlightComp->SetupAttachment(GetRootComponent());
	L_HeadlightComp->SetVisibility(false);
	L_HeadlightComp->CastShadows = false;
	
	R_HeadlightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("R_HeadlightComp"));
	R_HeadlightComp->SetupAttachment(GetRootComponent());
	R_HeadlightComp->SetVisibility(false);
	R_HeadlightComp->CastShadows = false;
	
	// Simulation
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	 check(Vehicle4W->WheelSetups.Num() == 4);

	 Vehicle4W->WheelSetups[0].WheelClass = UProject_157WheelFront::StaticClass();
	 Vehicle4W->WheelSetups[0].BoneName = FName("Wheel_Front_Left");
	 Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);
	
	 Vehicle4W->WheelSetups[1].WheelClass = UProject_157WheelFront::StaticClass();
	 Vehicle4W->WheelSetups[1].BoneName = FName("Wheel_Front_Right");
	 Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);
	
	 Vehicle4W->WheelSetups[2].WheelClass = UProject_157WheelRear::StaticClass();
	 Vehicle4W->WheelSetups[2].BoneName = FName("Wheel_Rear_Left");
	 Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -12.f, 0.f);
	
	 Vehicle4W->WheelSetups[3].WheelClass = UProject_157WheelRear::StaticClass();
	 Vehicle4W->WheelSetups[3].BoneName = FName("Wheel_Rear_Right");
	 Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	//Setup TextRenderMaterial
	static ConstructorHelpers::FObjectFinder<UMaterial> TextMaterial(TEXT("Material'/Engine/EngineMaterials/AntiAliasedTextMaterialTranslucent.AntiAliasedTextMaterialTranslucent'"));
	
	UMaterialInterface* Material = TextMaterial.Object;
	bInReverseGear = false;
}

void AProject_157BaseVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Accelerate/Reverse", this, &AProject_157BaseVehicle::Input_MoveForward);
	PlayerInputComponent->BindAxis("Steer", this, &AProject_157BaseVehicle::Input_MoveRight);
	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AProject_157BaseVehicle::Input_OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AProject_157BaseVehicle::Input_OnHandbrakeReleased);
	PlayerInputComponent->BindAction("Headlight", IE_Pressed, this, &AProject_157BaseVehicle::Input_ToggleHeadlight);
}



void AProject_157BaseVehicle::BeginPlay()
{
	Super::BeginPlay();

	Controller = nullptr;
}

void AProject_157BaseVehicle::Tick(float Delta)
{
	Super::Tick(Delta);
	
	// Setup the flag to say we are in reverse gear
	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;
	
}


void AProject_157BaseVehicle::Input_MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
	UE_LOG(LogTemp,Warning,TEXT("%f"), Val);
}

void AProject_157BaseVehicle::Input_MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void AProject_157BaseVehicle::Input_OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AProject_157BaseVehicle::Input_OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AProject_157BaseVehicle::Input_ToggleHeadlight()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
	bool bToggle = !L_HeadlightComp->IsVisible();
	R_HeadlightComp->SetVisibility(bToggle);
	L_HeadlightComp->SetVisibility(bToggle);
}


FVector AProject_157BaseVehicle::QueryExitLocation()
{
	// we get the exit door locations from blueprint (scene components)
	TArray<FVector> exitLocations = ExitDoorLocations();
	FVector desiredLoc = GetActorLocation();

	if(exitLocations.Num() ==	0)
	{
		UE_LOG(LogTemp,Display,TEXT("%s : We found a BAD location to exit vehicle."), *FString(__FUNCTION__))
		return desiredLoc;
	}
	
	for(const auto& it : exitLocations)
	{
		FHitResult cacheHitResult = GetCapsuleCollisionForExitDoorLocation(it);
		if(!cacheHitResult.bBlockingHit)
		{
			desiredLoc = cacheHitResult.TraceEnd;
			UE_LOG(LogTemp,Display,TEXT("%s : We found a good location to exit vehicle. LOC: %s / %s"), *FString(__FUNCTION__),
				*FString(desiredLoc.ToString()), *FString(GetCapsuleCollisionForExitDoorLocation((it)).Location.ToString()));
			break;
		}		
	}
	
	//UE_LOG(LogTemp,Display,TEXT("%s : We found a BAD location to exit vehicle."), *FString(__FUNCTION__))
	return desiredLoc;
}

FHitResult AProject_157BaseVehicle::GetCapsuleCollisionForExitDoorLocation(FVector ExitDoorLocation)
{
	// Physics collision query
	FHitResult OutHit;	
	const FVector startLocation = ExitDoorLocation;
	const FVector endLocation =  ExitDoorLocation;
	const float radius = PawnPossessing ? PawnPossessing->GetCapsuleComponent()->GetScaledCapsuleRadius() : 34.F;
	const float halfHeight =PawnPossessing ? PawnPossessing->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() : 88.F;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = ExitDoorCollisionTypes();
	constexpr bool bTraceComplex  = true;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	ActorsToIgnore.Add(this);
	
	UKismetSystemLibrary::CapsuleTraceSingleForObjects(GetOwner(), startLocation, endLocation,
		radius, halfHeight, ObjectTypes, bTraceComplex, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Green, FLinearColor::Yellow, 6.f);
	
	return OutHit;
}

void AProject_157BaseVehicle::RequestEnterVehicle_Implementation(AActor* ActorRequested)
{
	IProject_157VehicleInterface::RequestEnterVehicle_Implementation(ActorRequested);
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));

	if(GetController())
	{
		GetController()->UnPossess();
	}

	// Enter vehicle, check if it's controlled pawn by a human, then possess this vehicle.	
	if(AController* controller = Cast<AController>(ActorRequested))
	{		
		if(controller->IsPlayerController())
		{
			// we assume that pawns that can possess vehicles are at least of type ACharacter. It's fine for now, 
			PawnPossessing = Cast<ACharacter>(controller->GetPawn());
			controller->ResetIgnoreMoveInput();
			controller->Possess(this);
		}
	}
}

void AProject_157BaseVehicle::RequestExitVehicle_Implementation(AActor* ActorRequested,  FVector& ExitLocation, FRotator& ExitRotation)
{	
	// Query collision to find proper location to exit character capsule.
	ExitLocation = QueryExitLocation();
	
	//Desired rotation = car forward rotation	
	ExitRotation = FRotator(0, GetActorRotation().Yaw, 0.F);
	
	
	IProject_157VehicleInterface::RequestExitVehicle_Implementation(ActorRequested, ExitLocation, ExitRotation);

	PawnPossessing = nullptr;
	GetVehicleMovement()->StopMovementImmediately();
	GetVehicleMovement()->SetHandbrakeInput(true);	
}

void AProject_157BaseVehicle::SetController(AController* NewController)
{
	if(!NewController)
		return;
	
	check(GetVehicleMovement())
	
	
	GetVehicleMovement()->SetOverrideController(NewController);
	Controller = NewController;
	NewController->Possess(this);
	this->ReceivePossessed(NewController);
	
}

#undef LOCTEXT_NAMESPACE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
