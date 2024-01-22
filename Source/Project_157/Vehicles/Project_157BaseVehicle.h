// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Project_157/Interfaces/Project_157VehicleInterface.h"
#include "Project_157BaseVehicle.generated.h"

class USpotLightComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputComponent;

PRAGMA_DISABLE_DEPRECATION_WARNINGS

UCLASS(config=Game)
class AProject_157BaseVehicle : public AWheeledVehicle, public IProject_157VehicleInterface
{
	GENERATED_BODY()

public:
	AProject_157BaseVehicle(const FObjectInitializer& ObjectInitializer);
	
	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpotLightComponent* R_HeadlightComp;	
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpotLightComponent* L_HeadlightComp;
	
	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;

	
	/** Handle pressing forwards */
	void Input_MoveForward(float Val);
	/** Handle pressing right */
	void Input_MoveRight(float Val);
	/** Handle handbrake pressed */
	void Input_OnHandbrakePressed();
	/** Handle handbrake released */
	void Input_OnHandbrakeReleased();
	/**	Handle car headlights pressed */
	void Input_ToggleHeadlight();
	
	static const FName LookUpBinding;
	static const FName LookRightBinding;

	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

#pragma region Inherited Interfaces
	
	virtual void RequestEnterVehicle_Implementation(AActor* ActorRequested) override;
	virtual void RequestExitVehicle_Implementation(AActor* ActorRequested,  FVector& ExitLocation, FRotator& ExitRotation) override;
	
#pragma endregion

	// GETTERS
	UFUNCTION(BlueprintPure, Category=Getters)
	FORCEINLINE float GetThrottleInput() const
	{
		return 0.f;
	}

	UFUNCTION(BlueprintCallable)
	void SetController(AController* NewController);
	
protected:
	virtual void BeginPlay() override;

	/* Pawn that is possessing this vehicle */
	UPROPERTY()
	ACharacter* PawnPossessing; 

	FVector QueryExitLocation();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<FVector> ExitDoorLocations();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<TEnumAsByte<EObjectTypeQuery>> ExitDoorCollisionTypes();

	// Helper function for querying exit locations with capsule trace
	FHitResult GetCapsuleCollisionForExitDoorLocation(FVector ExitDoorLocation);

private:
	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;
};

PRAGMA_ENABLE_DEPRECATION_WARNINGS

