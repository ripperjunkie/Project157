// Copyright (c) 2024 @ Rafael Zagolin


#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Project_157Utils.generated.h"

#define DOUBLE_PI (3.141592653589793238462643383279502884197169399)
#define RAD_TO_DEG(x) 180.F / DOUBLE_PI * x

class USoundCue;
class USkeletalMesh;

UENUM(BlueprintType)
enum class EProject_157ActionState : uint8
{
	Walking = 0,
	Aiming = 1 << 0, 
	Shooting = 1 << 1,
	Melee = 1 << 2, 
	Crouching = 1 << 3, 
	ChargeJump = 1 << 4, 
	Sprinting = 1 << 5, 
	WeaponEquipped = 1 << 6, 
};

/* State that defines current weapon character is holding */
UENUM(BlueprintType)
enum class EProject_157Weapon : uint8
{
	None = 0,
	AR4 = 1 << 0,
	G67_Grenade = 1 << 1,
	KA_Val = 1 << 2,
	KA_47 = 1 << 3, /* walking or running */
	KA74U = 1 << 4,
	M9_Knife = 1 << 5,
	SMG_11 = 1 << 6
};

UENUM(BlueprintType)
enum class EProject_157WeaponFireType : uint8
{
	SemiAutomatic,
	Automatic,
	Burst
};

USTRUCT(BlueprintType)
struct FProject_157ItemData :  public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* ItemIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	USkeletalMesh* ItemSK;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector RelativeLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator RelativeRotation;
	
};

USTRUCT(BlueprintType)
struct FProject_157WeaponData :  public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	/*Total ammo amount that is not in the current clip*/	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalRemainingAmmo = 100;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmoPerClip = 30;
	/*Clips amount to give when player picks up a new weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClipsAmountToCollect = 3;	
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Bullet settings")
	uint8 bInfiniteBullets : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Hitscan")
	uint8 bHitscan : 1;
	

	
	UPROPERTY(BlueprintReadWrite)
	FVector MuzzleLocation; // where the bullets come from, interface from player
	
	UPROPERTY(BlueprintReadWrite)
	FVector Direction; // where the bullets come from, interface from player

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Hitscan")
	float BulletRange = 1000.f;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle FireRateTimer; // where the bullets come from, interface from player
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = .5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProject_157WeaponFireType WeaponFireType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProject_157Weapon Weapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* ShootingSound;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* ReloadingSound;		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* OutOfAmmoSound;
	


	/* DEBUG */
	UPROPERTY(EditAnywhere, Category=Debug)
	uint8 bDebug : 1;
	UPROPERTY(EditAnywhere, Category=Debug)
	uint8 Debug_Persistent : 1;
	UPROPERTY(EditAnywhere, Category=Debug)
	float Debug_LifeTime = 1.f;
	UPROPERTY(EditAnywhere, Category=Debug)
	float Debug_Thickness = 1.f;	
	UPROPERTY(EditAnywhere, Category=Debug)
	FColor Debug_Color = FColor::Green;
};

USTRUCT(BlueprintType)
struct FProject_157InputSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D MouseSensitivity;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector2D GamepadSensitivity;	
};



USTRUCT(BlueprintType)
struct FProject_157PlayerData :  public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultFOV;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AimFOV;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefaultArmLength = 450.f;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AimArmLength = 350.f;
};

USTRUCT(BlueprintType)
struct FProject_157DefaultMovementSettings
{
	GENERATED_BODY()

	/** Equivalent to character default speed. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float MaxWalkSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float MaxAcceleration;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float GroundFriction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float GravityScale;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float BrakingDecelerationWalking;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float JumpZVelocity;
};

USTRUCT(BlueprintType)
struct FProject_157MovementSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RunWalkSpeed = 550.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CrouchWalkSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AimWalkSpeed = 200.f;
};