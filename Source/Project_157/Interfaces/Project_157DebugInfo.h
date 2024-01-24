// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project_157/Public/Project_157Utils.h"
#include "Project_157DebugInfo.generated.h"

class UProject_157SprintComponent;
class UProject_157WeaponComponent;
class UProject_157InventoryComponent;
class UProject_157AimComponent;
class UProject_157HealthComponent;
class UCharacterMovementComponent;

// This class does not need to be modified.
UINTERFACE()
class UProject_157DebugInfo : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_157_API IProject_157DebugInfo
{
	GENERATED_BODY()

public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual UCharacterMovementComponent* Debug_GetCharacterMovementComponent() const = 0;
	virtual UProject_157HealthComponent* Debug_GetHealthComponent() const = 0;
	virtual UProject_157AimComponent* Debug_GetAimComponent() const = 0;
	virtual UProject_157InventoryComponent* Debug_GetInventoryComponent() const = 0;
	virtual UProject_157WeaponComponent* Debug_GetWeaponComponent() const = 0;
	virtual UProject_157SprintComponent* Debug_GetSprintComponent() const = 0;
	virtual bool Debug_CharacterState(EProject_157ActionState ActionState) = 0;
};