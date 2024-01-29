// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Project_157/Public/Project_157Utils.h"

#include "Project_157ItemComponent.generated.h"

class AProject_157HeroItem;

DECLARE_LOG_CATEGORY_EXTERN(Log_Project_157ItemComponent, Display, All);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_157_API UProject_157ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProject_157ItemComponent();

	virtual void Start_UsingItem();
	virtual void Stop_UsingItem();
	
	// this function will be used for every item that already exists when the player is trying to pickup, so this function will get called
	virtual void AddingExistingItem(); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProject_157HeroItem> HeroItem;

	// Item data to use for lookup table
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProject_157ItemData ItemData;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsUsingItem() const
	{
		return bUsingItem;
	}

	UFUNCTION(BlueprintSetter)
	void SetCanUseItem(bool _CanUseItem);

	__forceinline bool CanUseItem() const
	{
		return bCanUseItem;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	uint8 bUsingItem : 1;

	UPROPERTY(BlueprintReadOnly)
	uint8 bCanUseItem : 1;
	
};
