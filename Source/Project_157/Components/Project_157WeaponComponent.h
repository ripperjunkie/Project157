// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "Project_157ItemComponent.h"
#include "Components/ActorComponent.h"
#include "Project_157/Public/Project_157Utils.h"

#include "Project_157WeaponComponent.generated.h"


class AProject_157Player;

DECLARE_LOG_CATEGORY_EXTERN(LogCS_WeaponComponent, Display, All);


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_157_API UProject_157WeaponComponent : public UProject_157ItemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProject_157WeaponComponent();

	virtual void Start_UsingItem() override;
	virtual void Stop_UsingItem() override;
	virtual void AddingExistingItem() override;
	virtual void StartShooting();
	virtual void StopShooting();
	virtual void TryReload();

	UPROPERTY()
	int32 CurrentEquippedWeapon;

	UPROPERTY()
	AProject_157Player* PlayerRef;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle WasShootingTimer;		

	UPROPERTY(EditAnywhere)
	float WasShootingTimerF = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProject_157WeaponData WeaponCodeData;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShootSound();	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayReloadSound();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Shoot();
	virtual void Hitscan();
	virtual void SpawnProjectile();
	FHitResult CameraTrace_Helper();

};
