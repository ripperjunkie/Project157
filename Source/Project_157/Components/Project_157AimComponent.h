// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_157AimComponent.generated.h"

class AProject_157Player;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_157_API UProject_157AimComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProject_157AimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	/* not the best solution to create a direct reference
 * to the player character but let's do this quick solution for now
 */
	UPROPERTY()
	AProject_157Player* PlayerRef;

	UFUNCTION(BlueprintCallable)
	void StartAim();

	UFUNCTION(BlueprintCallable)
	void StopAim();

	UFUNCTION(BlueprintCallable)
	void ToggleAim(bool aiming);
};
