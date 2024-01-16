// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project_157PlayerController.generated.h"



class UProject_157EnterExitVehicleComponent;
/**
 * 
 */
UCLASS()
class PROJECT_157_API AProject_157PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProject_157PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Components")
	UProject_157EnterExitVehicleComponent* EnterExitVehicleComponent;
	
};
