// Copyright (c) 2024 @ Rafael Zagolin


#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Project_157Utils.generated.h"

class USoundCue;
class USkeletalMesh;

UENUM(BlueprintType)
enum class EProject_157ActionState : uint8
{
	Walking = 0,
	Aiming = 1 << 0, // 1
	Shooting = 1 << 1, // 2
	Melee = 1 << 2, // 4
	Dashing = 1 << 3, // 8
	ChargeJump = 1 << 4, // 16
	OnHoverboard = 1 << 5, // 32
	WeaponEquipped = 1 << 6, // 64
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
	TWeakObjectPtr<USkeletalMesh> ItemSK;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProject_157Weapon Weapon;
};

USTRUCT(BlueprintType)
struct FProject_157WeaponData
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
struct FDefaultMovementSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxAcceleration;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float GroundFriction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float GravityScale;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BrakingDecelerationWalking;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float JumpZVelocity;
};

USTRUCT(BlueprintType)
struct FProject_157PlayerData :  public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimFOV;
};