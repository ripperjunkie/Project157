// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project_157CharacterInterface.generated.h"

class UProject_157ItemComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProject_157CharacterInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_157_API IProject_157CharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* Tell it to update necessary things when cycling through inventory. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnChangeInventoryItem();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnShoot(FVector& _MuzzleLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnShoot_Camera(FVector& _MuzzleLocation, FVector& Direction);

	/* Having this method with the exact same signature from the Character class method might
	 * seem redundant, but we actually can expand it being an interface on classes that are not Character type.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FName BoneName = "");

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddItem(TSubclassOf<UProject_157ItemComponent> ItemToAdd);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CheckState(EProject_157ActionState stateToCheck);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCurrentState(EProject_157ActionState state);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetState(EProject_157ActionState state);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayFootstepSound();

	
	virtual void OnEnteredVehicle() = 0;
	virtual void OnExitedVehicle() = 0;

};
