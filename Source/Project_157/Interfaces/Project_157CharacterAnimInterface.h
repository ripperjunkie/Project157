// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Project_157/Public/Project_157Utils.h"


#include "Project_157CharacterAnimInterface.generated.h"

class ACharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProject_157CharacterAnimInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_157_API IProject_157CharacterAnimInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* Tell it to update necessary things when cycling through inventory. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetGroundSpeed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EProject_157ActionState GetCharacterState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EProject_157Weapon GetCurrentEquippedWeapon();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetCheckState(EProject_157ActionState State);
};
