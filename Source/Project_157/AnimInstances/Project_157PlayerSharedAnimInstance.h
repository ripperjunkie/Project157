// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Project_157PlayerSharedAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_157_API UProject_157PlayerSharedAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;
	
	UPROPERTY(BlueprintReadOnly)
	int32 GetCharacterState;
	
	UPROPERTY(BlueprintReadOnly)
	int32 GetEquippedWeapon;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 bAiming : 1;
	
	UPROPERTY(BlueprintReadOnly)
	FVector2D GetLookAngle;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 bCrouching : 1;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	APawn* PawnOwner;
	
};
