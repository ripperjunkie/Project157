// Copyright (c) 2023 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_157HeroItem.generated.h"

class UBoxComponent;

UCLASS()
class PROJECT_157_API AProject_157HeroItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProject_157HeroItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UAudioComponent* ReloadAudioComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UAudioComponent* ShootAudioComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
