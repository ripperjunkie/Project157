// Copyright (c) 2023 @ Rafael Zagolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Project_157Player.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Log_Player, Log, All);

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECT_157_API AProject_157Player : public ACharacter
{
	GENERATED_BODY()
	

public:
	// Sets default values for this character's properties
	AProject_157Player(const FObjectInitializer& ObjectInitializer);


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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentActionState;

#pragma region Input related methods
	void Input_MoveForward(float Axis);
	void Input_MoveRight(float Axis);
	void Input_LookUp(float Axis);
	void Input_LookRight(float Axis);
#pragma endregion 
	
	
};
