// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project_157DebugInfo.generated.h"

class UCharacterMovementComponent;
// This class does not need to be modified.
UINTERFACE()
class UProject_157DebugInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_157_API IProject_157DebugInfo
{
	GENERATED_BODY()
public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual UCharacterMovementComponent* GetCharacterMovementComponent() const = 0;
};
