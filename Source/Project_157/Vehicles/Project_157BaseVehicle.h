// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Project_157/Interfaces/Project_157VehicleInterface.h"
#include "Project_157BaseVehicle.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;

PRAGMA_DISABLE_DEPRECATION_WARNINGS

UCLASS(config=Game)
class AProject_157BaseVehicle : public AWheeledVehicle, public IProject_157VehicleInterface
{
	GENERATED_BODY()

public:
	AProject_157BaseVehicle();
	
	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;

	
	/** Handle pressing forwards */
	void MoveForward(float Val);

	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();
	
	static const FName LookUpBinding;
	static const FName LookRightBinding;

	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

#pragma region Inherited Interfaces
	
	virtual void RequestEnterVehicle_Implementation(AActor* ActorRequested) override;
	
#pragma endregion
	
protected:
	virtual void BeginPlay() override;

private:
	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;


};

PRAGMA_ENABLE_DEPRECATION_WARNINGS

