// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157DamageFilter.h"


// Sets default values for this component's properties
UProject_157DamageFilter::UProject_157DamageFilter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UProject_157DamageFilter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	
}

float UProject_157DamageFilter::FilteredDamage(float DamageTaken, FName Bone)
{		
	float resistance = 0.f;
	
	// Define a predicate function to find the correct element
	auto Predicate = [Bone](const FProject_157BodyPartDamage& Element)
	{
		return Element.Bone == Bone;
	};

	FProject_157BodyPartDamage* _bodyPart = BodyPartDamage.FindByPredicate(Predicate);

	
	if(!_bodyPart)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed-> %s: %f"), *FString(__FUNCTION__), resistance);
		return DamageTaken;
	}	
	resistance = _bodyPart->Resistance;
	
	UE_LOG(LogTemp, Warning, TEXT("Succeeded-> %s: %f"), *FString(__FUNCTION__), resistance);
	return FMath::Abs(DamageTaken) - (FMath::Abs(DamageTaken) * resistance);	
	
}



