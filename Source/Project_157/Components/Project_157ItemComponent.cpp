// Copyright (c) 2023 @ Rafael Zagolin


#include "Project_157ItemComponent.h"
#include "Project_157/Items/Project_157HeroItem.h"

// Sets default values for this component's properties
UProject_157ItemComponent::UProject_157ItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UProject_157ItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UProject_157ItemComponent::Start_UsingItem()
{
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
