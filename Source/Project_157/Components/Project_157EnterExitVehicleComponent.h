// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_157EnterExitVehicleComponent.generated.h"

class UCapsuleComponent;



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_157_API UProject_157EnterExitVehicleComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class AProject_157Player;

public:
	// Sets default values for this component's properties
	UProject_157EnterExitVehicleComponent();

	// Methods to enter and exit vehicle	
	UFUNCTION()
	void RequestVehicleInteraction();
	UFUNCTION(BlueprintCallable)
	void RequestEnterVehicle();
	UFUNCTION(BlueprintCallable)
	void RequestExitVehicle();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// We process collisions here to keep logic organized
	UFUNCTION(BlueprintCallable)
	FHitResult CanEnterVehicle();
	


	UPROPERTY(BlueprintReadOnly)
	uint8 bInVehicleEnterCollision : 1;

private:
	UPROPERTY()
	UCapsuleComponent* OwnerCapsuleComp;
	

public:
	// // Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	//                            FActorComponentTickFunction* ThisTickFunction) override;
};