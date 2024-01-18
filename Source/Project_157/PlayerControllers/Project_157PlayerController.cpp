// Copyright (c) 2024 @ Rafael Zagolin

#include "Project_157PlayerController.h"
#include "Project_157/Components/Project_157EnterExitVehicleComponent.h"


AProject_157PlayerController::AProject_157PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Creating enter exit vehicle component */
	EnterExitVehicleComponent = CreateDefaultSubobject<UProject_157EnterExitVehicleComponent>(TEXT("EnterExitVehicle Component"));
}

void AProject_157PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);
	InputComponent->BindAction("EnterExitVehicle", IE_Pressed, EnterExitVehicleComponent, &UProject_157EnterExitVehicleComponent::RequestVehicleInteraction);
}

void AProject_157PlayerController::BeginPlay()
{
	Super::BeginPlay();

}
