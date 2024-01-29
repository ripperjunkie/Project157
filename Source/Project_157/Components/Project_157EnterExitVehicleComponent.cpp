// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157EnterExitVehicleComponent.h"

#include "Project_157Utils.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Project_157/Interfaces/Project_157CharacterInterface.h"
#include "Project_157/Interfaces/Project_157VehicleInterface.h"

// Sets default values for this component's properties
UProject_157EnterExitVehicleComponent::UProject_157EnterExitVehicleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UProject_157EnterExitVehicleComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const AController* controller = Cast<AController>(GetOwner()))
	{
		if(ACharacter* character = Cast<ACharacter>(controller->GetPawn()))			
			OwnerCapsuleComp = character->GetCapsuleComponent();		
	}
}

void UProject_157EnterExitVehicleComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
		Super::EndPlay(EndPlayReason);
}

void UProject_157EnterExitVehicleComponent::RequestVehicleInteraction()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
	// Check if player is possessing a vehicle or is in vehicle already
	APlayerController* controller = Cast<APlayerController>(GetOwner());
	
	if(controller->IsPlayerController())
	{
		if(ACharacter* possessedCharacter = Cast<ACharacter>(controller->GetPawn()))
		{
			// let's store our current possessed character pawn
			CurrentPossessedCharacter = possessedCharacter;
			
			RequestEnterVehicle();
			UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
			return;
		}
	}
	if(CurrentPossessedVehicle == controller->GetPawn())
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));

		RequestExitVehicle();
	}
}

void UProject_157EnterExitVehicleComponent::RequestEnterVehicle()
{	
	// Check if character is nearby vehicle to enter	
	const FHitResult hitResult = CanEnterVehicle();
	if(!hitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Does not block hit."));
		return;		
	}

	// hide character mesh, deactivate collision
	APlayerController* controller = Cast<APlayerController>(GetOwner());
	if(ACharacter* possessedCharacter = Cast<ACharacter>(	controller->GetPawn()	)	)
	{
		// let's store our current possessed character pawn
		CurrentPossessedCharacter = possessedCharacter;
		CurrentPossessedCharacter->SetActorEnableCollision(false);
		CurrentPossessedCharacter->SetActorHiddenInGame(true);

		// Set driving state in driver pawn
		IProject_157CharacterInterface* CharacterInterface = Cast<IProject_157CharacterInterface>(possessedCharacter);
		if(CharacterInterface)
		{
			CharacterInterface->SetCurrentState_Implementation(EProject_157ActionState::Driving);
		}
	}

	// store vehicle ref
	AActor* vehicle = hitResult.GetActor();
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(vehicle->GetName()));
	if(!vehicle)
	{
		return;
	}
	
	if(IProject_157VehicleInterface* interface = Cast<IProject_157VehicleInterface>(vehicle))
	{
		// We pass the owner assuming that it's a player controller	
		IProject_157VehicleInterface::Execute_RequestEnterVehicle(vehicle, Cast<AActor>(GetOwner()));
		
		CurrentPossessedVehicle = vehicle;
		
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
	}

}

void UProject_157EnterExitVehicleComponent::RequestExitVehicle()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
	
	APlayerController* controller = Cast<APlayerController>(GetOwner());
	
	if(!controller)
	{
		return;
	}
	FVector BestExitLocation;
	FRotator BestExitRotation;
	IProject_157VehicleInterface::Execute_RequestExitVehicle(CurrentPossessedVehicle, controller, BestExitLocation, BestExitRotation);
	
	if(controller)
	{
		CurrentPossessedCharacter->SetActorEnableCollision(true);
		CurrentPossessedCharacter->SetActorHiddenInGame(false);
		CurrentPossessedCharacter->SetActorLocation(BestExitLocation);		
		controller->Possess(CurrentPossessedCharacter);
		CurrentPossessedVehicle = nullptr;

		// Set driving state in driver pawn
		IProject_157CharacterInterface* CharacterInterface = Cast<IProject_157CharacterInterface>(CurrentPossessedCharacter);
		if(CharacterInterface)
		{
			CharacterInterface->ResetState_Implementation(EProject_157ActionState::Driving);
		}
		
	}	
}

FHitResult UProject_157EnterExitVehicleComponent::CanEnterVehicle()
{
	// Physics collision query
	const FVector startLocation = OwnerCapsuleComp->GetComponentLocation();
	const FVector endLocation =  OwnerCapsuleComp->GetComponentLocation();
	const float radius = OwnerCapsuleComp->GetScaledCapsuleRadius();
	const float halfHeight = OwnerCapsuleComp->GetScaledCapsuleHalfHeight();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery5);
	constexpr  bool bTraceComplex  = true;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult OutHit;
	
	
	
	UKismetSystemLibrary::CapsuleTraceSingleForObjects(GetOwner(), startLocation, endLocation,
		radius, halfHeight, ObjectTypes, bTraceComplex, ActorsToIgnore,
		EDrawDebugTrace::None, OutHit, true, FLinearColor::Green, FLinearColor::Red, 3.f);
	
	return OutHit;
}
