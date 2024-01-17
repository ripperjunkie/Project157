// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project_157VehicleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProject_157VehicleInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_157_API IProject_157VehicleInterface
{
	GENERATED_BODY()
	
public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RequestEnterVehicle(AActor* ActorRequested);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RequestExitVehicle(AActor* ActorRequested, FVector& ExitLocation, FRotator& ExitRotation);

public:
};
