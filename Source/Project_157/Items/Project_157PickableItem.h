// Copyright (c) 2023 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_157/Interfaces/Project_157ItemInterface.h"

#include "Project_157PickableItem.generated.h"

class UProject_157ItemComponent;
class UBoxComponent;


UCLASS()
class PROJECT_157_API AProject_157PickableItem : public AActor, public IProject_157ItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProject_157PickableItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Components)
	USceneComponent* DefaultSceneComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Components)
	UStaticMeshComponent* StaticMeshComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Collision)
	UBoxComponent* BoxCollision;
	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProject_157ItemComponent> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName_Debug;

	virtual void PickupItem_Implementation(AActor* InteractActor) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
