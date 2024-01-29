// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157ItemComponent.h"

DEFINE_LOG_CATEGORY(Log_Project_157ItemComponent);

// Sets default values for this component's properties
UProject_157ItemComponent::UProject_157ItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bCanUseItem = true;
	bUsingItem = false;

}

void UProject_157ItemComponent::SetCanUseItem(bool _CanUseItem)
{
	bCanUseItem = _CanUseItem;
}

// Called when the game starts
void UProject_157ItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UProject_157ItemComponent::Start_UsingItem()
{
	if(!bCanUseItem)
	{
		UE_LOG(Log_Project_157ItemComponent, Display, TEXT("%s: cannot use item."), *FString(__FUNCTION__));
		return;
	}
		
	bUsingItem = true;
}

void UProject_157ItemComponent::Stop_UsingItem()
{
	bUsingItem = false;
}

void UProject_157ItemComponent::AddingExistingItem()
{
	// Write your own implementation
}
