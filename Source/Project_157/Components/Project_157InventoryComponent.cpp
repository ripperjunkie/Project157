// Copyright (c) 2023 @ Rafael Zagolin


#include "Project_157InventoryComponent.h"

#include "Project_157/Interfaces/Project_157CharacterInterface.h"
#include "Project_157ItemComponent.h"

// Sets default values for this component's properties
UProject_157InventoryComponent::UProject_157InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UProject_157InventoryComponent::StopUsingItemRequest()
{
	if (!GetCurrentItem())
	{
		return;
	}
	if (UProject_157ItemComponent* item = GetCurrentItem())
	{
		item->Stop_UsingItem();
	}
}

// Called when the game starts
void UProject_157InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Helper function to update hero selected weapon
void UProject_157InventoryComponent::UpdateCharacter()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));

	AActor* actor = GetOwner();

	if (!actor)
		return;

	if (IProject_157CharacterInterface* heroInterface = Cast<IProject_157CharacterInterface>(actor))
	{
		IProject_157CharacterInterface::Execute_OnChangeInventoryItem(actor);
	}
}


void UProject_157InventoryComponent::CycleUp()
{
	//CurrentSelectedItem = FMath::Clamp(CurrentSelectedItem + 1, -1, Items.Num() - 1);
	const int lastIndex = Items.Num() - 1;
	if (CurrentSelectedItem + 1 <= lastIndex)
	{
		CurrentSelectedItem += 1;
	}
	else
	{
		// no item
		CurrentSelectedItem = -1;
	}

	UpdateCharacter();
}

void UProject_157InventoryComponent::CycleDown()
{
	//CurrentSelectedItem = FMath::Clamp(CurrentSelectedItem + 1, -1, Items.Num() - 1);
	const int noItem = -1;
	if (CurrentSelectedItem - 1 >= noItem)
	{
		CurrentSelectedItem -= 1;
	}
	else
	{
		// no item
		CurrentSelectedItem = Items.Num() - 1;
	}

	UpdateCharacter();
}

void UProject_157InventoryComponent::NoWeapon()
{
	// Change to no equipped weapon
	CurrentSelectedItem = -1;
	UpdateCharacter();
}


void UProject_157InventoryComponent::AddToInventory(UProject_157ItemComponent* _ItemToAdd)
{
	// already has that item
	if (QueryInventoryItem(_ItemToAdd))
	{
		return;
	}

	if (Items.Num() < InventoryCapacity)
	{
		Items.Add(_ItemToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full!"));
	}
	UpdateCharacter();
}

void UProject_157InventoryComponent::RemoveToInventory(UProject_157ItemComponent* _ItemToRemove)
{
	Items.Remove(_ItemToRemove);
	UpdateCharacter();
}


// Helper function that will check to see if we already have that existing inventory item
bool UProject_157InventoryComponent::QueryInventoryItem(UProject_157ItemComponent* _ItemToAdd)
{
	//int indexFound = 0;
	//Items.Find(_ItemToAdd, indexFound);

	for (UProject_157ItemComponent*& item : Items)
	{
		if(item->GetClass() == _ItemToAdd->GetClass())
		{
			item->AddingExistingItem();
				UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Item exists on inventory"));
			return true;
		}
	}
	 UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Item doesn't exist on inventory"));
	return false;

	
	// if (indexFound != INDEX_NONE)
	// {
	// 	Items[indexFound]->AddingExistingItem();
	// 	UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Item exists on inventory"));
	//
	// 	return true;
	// }
	// UE_LOG(LogTemp, Display, TEXT("%s"), *FString("Item doesn't exist on inventory"));
	//
	// return false;
}
