// Copyright (c) 2023 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_157/Interfaces/Project_157CharacterInterface.h"

#include "Project_157Player.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Log_Player, Log, All);

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECT_157_API AProject_157Player : public ACharacter, public IProject_157CharacterInterface
{
	GENERATED_BODY()
	

public:
	// Sets default values for this character's properties
	AProject_157Player(const FObjectInitializer& ObjectInitializer);

	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool CheckState(EProject_157ActionState stateToCheck);

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EProject_157ActionState state);

	UFUNCTION(BlueprintCallable)
	void ResetState(EProject_157ActionState state);

	UPROPERTY()
	int32 CurrentActionState;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

#pragma region Default Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Default Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Default Components")
	UCameraComponent* CameraComponent;

#pragma endregion


#pragma region Input related methods
	
	void Input_MoveForward(float Axis);
	void Input_MoveRight(float Axis);
	void Input_LookUp(float Axis);
	void Input_LookRight(float Axis);
	
#pragma endregion

#pragma region IProject_157CharacterInterface Methods

	virtual void OnChangeInventoryItem_Implementation() override;
	virtual void OnShoot_Implementation(FVector& _MuzzleLocation) override;
	virtual void OnShoot_Camera_Implementation(FVector& _MuzzleLocation, FVector& Direction) override;
	virtual void TakeDamage_Implementation(float _Damage, AActor* DamageCauser) override;
	virtual void AddItem_Implementation(TSubclassOf<UProject_157ItemComponent> ItemToAdd) override;
	
#pragma endregion

	
	
	
	
};
