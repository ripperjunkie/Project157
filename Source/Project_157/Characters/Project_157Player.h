// Copyright (c) 2024 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_157/Interfaces/Project_157CharacterAnimInterface.h"
#include "Project_157/Interfaces/Project_157CharacterInterface.h"
#include "Project_157/Interfaces/Project_157DebugInfo.h"
#include "Project_157/Public/Project_157Utils.h"

#include "Project_157Player.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProject_157Player, Log, All);

class DebugImGui;
class UProject_157AimComponent;
class UProject_157SprintComponent;
class UProject_157InventoryComponent;
class UProject_157HealthComponent;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USceneComponent;


UCLASS()
class PROJECT_157_API AProject_157Player : public ACharacter, public IProject_157CharacterInterface,
public IProject_157CharacterAnimInterface, public IProject_157DebugInfo
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AProject_157Player(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool CheckEquippedWeapon(EProject_157Weapon EquippedWeapon);

	/* Set current equipped weapon for weapon state type */
	UFUNCTION(BlueprintCallable)
	void SetCurrentEquippedWeaponType(EProject_157Weapon state);

	UFUNCTION(BlueprintCallable)
	void ResetCurrentEquippedWeaponState(EProject_157Weapon state);

	/* This might have to be moved to the player controller so we can store
	 * info about our character state. Also it might be a good idea if we create
	 * a component that can manage this character states.
	 */
	UPROPERTY()
	int32 CurrentActionState;

	UPROPERTY()
	int32 CharacterConditionsStates;
	
	UPROPERTY()
	int32 CurrentEquippedWeapon;

#pragma region Getters
	
	UFUNCTION()
	FORCEINLINE FProject_157MovementSettings GetMovementSettings() const
	{
		return MovementSettings;
	}
	
	UFUNCTION()
	FORCEINLINE FProject_157DefaultMovementSettings GetDefaultMovementSettings() const
	{
		return DefaultMovementSettings;
	}

	UFUNCTION()
	FORCEINLINE UProject_157SprintComponent* GetSprintComponent() const
	{
		return SprintComponent;
	}

	UFUNCTION()
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const
	{
		return SpringArmComponent;
	}

	UFUNCTION()
	FORCEINLINE UCameraComponent* GetCameraComponent() const
	{
		return CameraComponent;
	}

	UFUNCTION()
	FORCEINLINE UProject_157AimComponent* GetAimComponent() const
	{
		return AimComponent;
	}
	
	UFUNCTION()
	FORCEINLINE FProject_157PlayerData GetPlayerData() const
	{
		return PlayerData;
	}
	
	
#pragma endregion

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
#pragma region Default Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Default Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Default Components")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Default Components")
	USkeletalMeshComponent* WeaponSKComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UProject_157HealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UProject_157InventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UProject_157SprintComponent* SprintComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UProject_157AimComponent* AimComponent;
	
#pragma endregion

#pragma region Input related methods
	
	void Input_MoveForward(float Axis);
	void Input_MoveRight(float Axis);
	void Input_LookUp(float Axis);
	void Input_LookRight(float Axis);

	// Traversal actions
	void Input_Jump();
	void Input_Sprint();
	void Input_StartCrouch();
	void Input_StopCrouch();
	
	
	// Weapon Actions
	void Input_StartShoot();
	void Input_StopShoot();
	void Input_Reload();
	void Input_ItemCycleUp();
	void Input_ItemCycleDown();

	/** Called on blueprint when player asks to reload weapon. */
	UFUNCTION(BlueprintImplementableEvent)
	void Input_ReloadBP();
	
	
#pragma endregion

#pragma region IProject_157CharacterInterface 

	virtual void OnChangeInventoryItem_Implementation() override;
	virtual void OnShoot_Implementation(FVector& _MuzzleLocation) override;
	virtual void OnShoot_Camera_Implementation(FVector& _MuzzleLocation, FVector& Direction) override;
	virtual void TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FName BoneName = "") override;
	virtual void AddItem_Implementation(TSubclassOf<UProject_157ItemComponent> ItemToAdd) override;
	virtual bool CheckState_Implementation(EProject_157ActionState stateToCheck) override;
	virtual void SetCurrentState_Implementation(EProject_157ActionState state) override;
	virtual void ResetState_Implementation(EProject_157ActionState state) override;
	virtual void OnEnteredVehicle() override;
	virtual void OnExitedVehicle() override;
	
#pragma endregion

#pragma region IProject_157CharacterAnimInterface
	
	virtual float GetGroundSpeed_Implementation() override;
	virtual EProject_157ActionState GetCharacterState_Implementation() override;
	virtual EProject_157Weapon GetCurrentEquippedWeapon_Implementation() override;
	virtual bool GetCheckState_Implementation(EProject_157ActionState State) override;
	virtual float GetLookForwardAngle_Implementation() override;
	virtual float GetLookUpAngle_Implementation() override;	
	
#pragma endregion

#pragma region IProject_157DebugInfo
	
	virtual UCharacterMovementComponent* Debug_GetCharacterMovementComponent() const override
	{
		return GetCharacterMovement();
	}
	
	virtual UProject_157HealthComponent* Debug_GetHealthComponent() const override
	{
		return HealthComponent;
	}
	
	virtual UProject_157InventoryComponent* Debug_GetInventoryComponent() const override
	{
		return InventoryComponent;
	}
	virtual UProject_157WeaponComponent* Debug_GetWeaponComponent() const override;
	virtual UProject_157SprintComponent* Debug_GetSprintComponent() const override
	{
		return SprintComponent;
	}
	virtual UProject_157AimComponent* Debug_GetAimComponent() const override
	{
		return AimComponent;
	}
	virtual bool Debug_CharacterState(EProject_157ActionState ActionState) override
	{
		return CheckState_Implementation(ActionState);
	}
	
	
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProject_157PlayerData PlayerData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProject_157MovementSettings MovementSettings;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FProject_157DefaultMovementSettings DefaultMovementSettings;
	
	DebugImGui* Debug_ImGui;


	

};
