// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Project_157HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDieSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakeDamageSignature, float, Health, AActor*, DamageCauser);

DECLARE_LOG_CATEGORY_EXTERN(LogHealthComponent, Log, All);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_157_API UProject_157HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UProject_157HealthComponent();

	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	void SetInitialHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float InHealth);


	UFUNCTION(BlueprintCallable)
	void AddHealth(float InHealth);

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float InDamage, AActor* DamageCauser);

	UPROPERTY(EditAnywhere)
	bool bDebug;

	UPROPERTY(BlueprintAssignable)
	FOnDieSignature OnDieDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageSignature OnTakeDamageDelegate;


protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Params)
	float InitialHealth;

	UPROPERTY(EditDefaultsOnly, Category=Params)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category=Params)
	float MaxHealth;
};
