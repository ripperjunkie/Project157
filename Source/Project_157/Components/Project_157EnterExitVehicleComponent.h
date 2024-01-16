// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_157EnterExitVehicleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_157_API UProject_157EnterExitVehicleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProject_157EnterExitVehicleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// TODO: Add methods to enter and exit vehicle
	// void RequestEnterVehicle()
	// void RequestExitVehicle()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
