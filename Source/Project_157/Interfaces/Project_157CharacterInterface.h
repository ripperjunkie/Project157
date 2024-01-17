// Copyright (c) 2023 @ Rafael Zagolin

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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TakeDamage(float _Damage, AActor* DamageCauser);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddItem(TSubclassOf<UProject_157ItemComponent> ItemToAdd);
	
};
