// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_157/Public/Project_157Utils.h"

#include "Project_157DamageFilter.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_157_API UProject_157DamageFilter : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProject_157DamageFilter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FProject_157BodyPartDamage>  BodyPartDamage;

	UFUNCTION(BlueprintCallable)
	float FilteredDamage(float DamageTaken, FName Bone);
	
	
};
