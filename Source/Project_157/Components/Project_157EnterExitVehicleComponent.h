// Copyright (c) 2024 @ Rafael Zagolin

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

	// Methods for vehicle interaction	
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

private:
	UPROPERTY()
	ACharacter* CurrentPossessedCharacter;
	UPROPERTY()
	UCapsuleComponent* OwnerCapsuleComp;
	UPROPERTY()
	AActor* CurrentPossessedVehicle;
	

public:
	// // Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	//                            FActorComponentTickFunction* ThisTickFunction) override;
};
