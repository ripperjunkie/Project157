// Copyright (c) 2023 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_157InventoryComponent.generated.h"

class UProject_157ItemComponent;


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_157_API UProject_157InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProject_157InventoryComponent();
	
	UFUNCTION(BlueprintPure, Category=Accessor)
	FORCEINLINE TArray<UProject_157ItemComponent*> GetCurrentItems() const
	{
		return Items;
	}

	UFUNCTION(BlueprintPure, Category=Accessor)
	FORCEINLINE UProject_157ItemComponent* GetCurrentItem() const
	{
		const bool bIsValidindex = Items.IsValidIndex(CurrentSelectedItem);
		return Items.Num() > 0 && bIsValidindex ? Items[CurrentSelectedItem] : nullptr;
	}

	UFUNCTION(BlueprintCallable)
	void CycleUp();
	UFUNCTION(BlueprintCallable)
	void CycleDown();
	UFUNCTION(BlueprintCallable)
	void NoWeapon();

	UFUNCTION(BlueprintCallable)
	void AddToInventory(UProject_157ItemComponent* _ItemToAdd);	
	UFUNCTION(BlueprintCallable)
	void RemoveToInventory(UProject_157ItemComponent* _ItemToRemove);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventoryCapacity = 10;
	
	UFUNCTION(BlueprintCallable)
	void StopUsingItemRequest();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	UPROPERTY(BlueprintReadWrite, Category=Inventory)
	TArray<UProject_157ItemComponent*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentSelectedItem = 0;

	UFUNCTION(BlueprintPure)
	bool QueryInventoryItem(UProject_157ItemComponent* _ItemToAdd);

private:
	void UpdateCharacter();

};
