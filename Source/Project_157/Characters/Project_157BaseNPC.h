// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_157/Interfaces/Project_157CharacterInterface.h"


#include "Project_157BaseNPC.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogProject_157BaseEnemy, Log, All);

class UProject_157HealthComponent;


UCLASS()
class PROJECT_157_API AProject_157BaseNPC : public ACharacter, public IProject_157CharacterInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProject_157BaseNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

#pragma region IProject_157CharacterInterface 

	/* Override it by blueprint.*/
	virtual void OnShoot_Implementation(FVector& _MuzzleLocation) override;
	/* Override it by blueprint.*/
	virtual void OnShoot_Camera_Implementation(FVector& _MuzzleLocation, FVector& Direction) override;
	
	virtual void TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UProject_157HealthComponent* HealthComponent;
};
