// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_157EnterExitVehicleComponent.h"

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

	// ...
	
}


// Called every frame
void UProject_157EnterExitVehicleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

