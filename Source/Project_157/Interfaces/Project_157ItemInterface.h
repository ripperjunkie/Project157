// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Project_157ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProject_157ItemInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_157_API IProject_157ItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickupItem(AActor* InteractActor);
};