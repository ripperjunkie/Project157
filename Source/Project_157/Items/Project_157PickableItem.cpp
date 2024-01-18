// Copyright (c) 2024 @ Rafael Zagolin



#include "Project_157PickableItem.h"
#include "Components/BoxComponent.h"
#include "Project_157/Interfaces/Project_157CharacterInterface.h"

// Sets default values
AProject_157PickableItem::AProject_157PickableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
	DefaultSceneComp->SetupAttachment(RootComponent);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(DefaultSceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Static Mesh Comp"));
	StaticMeshComp->SetupAttachment(BoxCollision);
	
	ItemName_Debug = FString("None");
}


// Called when the game starts or when spawned
void AProject_157PickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProject_157PickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AProject_157PickableItem::PickupItem_Implementation(AActor* InteractActor)
{
	//ICS_ItemInterface::PickupItem_Implementation(InteractActor);

	UE_LOG(LogTemp, Display, TEXT("%s"), *FString(__FUNCTION__));
	if(InteractActor)
	{
		//  Pickup item
		if(IProject_157CharacterInterface* itemInterface = Cast<IProject_157CharacterInterface>(InteractActor))
		{
			if (itemInterface)
			{
				IProject_157CharacterInterface::Execute_AddItem(InteractActor, ItemClass);
			}
			Destroy();
		}
	}
}