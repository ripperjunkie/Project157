// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_157EnterExitVehicleComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
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
	// Check if player is possessing a vehicle or is in vehicle already
	APlayerController* controller = Cast<APlayerController>(GetOwner());
	if(!controller)
		return;

	if(controller->IsPlayerController())
	{
		if(ACharacter* possessedCharacter = Cast<ACharacter>(controller->GetPawn()))
		{
			RequestEnterVehicle();
			UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
			return;
		}
	}
	else if(Cast<IProject_157VehicleInterface>(controller->GetPawn()))
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
		RequestExitVehicle();
	}
}
void UProject_157EnterExitVehicleComponent::RequestEnterVehicle()
{	
	// TODO: Check if character is nearby vehicle to enter
	
	const FHitResult hitResult = CanEnterVehicle();
	if(!hitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Does not block hit."));
		return;		
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
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Does not implement interface"));
	}
}

void UProject_157EnterExitVehicleComponent::RequestExitVehicle()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
}

/*
 * const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, float HalfHeight, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes,
 * bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType,
 * FHitResult& OutHit, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime 
 */
FHitResult UProject_157EnterExitVehicleComponent::CanEnterVehicle()
{
	// TODO: Physics collision query
	const FVector startLocation = OwnerCapsuleComp->GetComponentLocation();
	const FVector endLocation =  OwnerCapsuleComp->GetComponentLocation();
	const float radius = OwnerCapsuleComp->GetScaledCapsuleRadius();
	const float halfHeight = OwnerCapsuleComp->GetScaledCapsuleHalfHeight();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery5);
	const bool bTraceComplex  = true;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult OutHit;
	
	
	
	UKismetSystemLibrary::CapsuleTraceSingleForObjects(GetOwner(), startLocation, endLocation,
		radius, halfHeight, ObjectTypes, bTraceComplex, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Green, FLinearColor::Red, 3.f);
	
	return OutHit;
}
