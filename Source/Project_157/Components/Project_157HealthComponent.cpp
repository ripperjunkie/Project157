// Copyright (c) 2023 @ Rafael Zagolin

#include "Project_157HealthComponent.h"

DEFINE_LOG_CATEGORY(LogHealthComponent);

UProject_157HealthComponent::UProject_157HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InitialHealth = 100.f;
	CurrentHealth = 100;
	MaxHealth = 100;
}


void UProject_157HealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UProject_157HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDebug)
	{
		UE_LOG(LogHealthComponent, Display, TEXT("CurrentHealth: %f"), CurrentHealth);
	}
}

float UProject_157HealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UProject_157HealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UProject_157HealthComponent::SetCurrentHealth(float InHealth)
{
	if (InHealth < MaxHealth)
	{
		CurrentHealth = InHealth;
	}
	else
	{
		CurrentHealth = MaxHealth;
	}
	if (InHealth <= 0)
	{
		CurrentHealth = 0;
		OnDieDelegate.Broadcast(CurrentHealth);
	}	
}

void UProject_157HealthComponent::SetInitialHealth(float InHealth)
{
	if (InHealth < MaxHealth)
	{
		InitialHealth = InHealth;
	}
}

void UProject_157HealthComponent::SetMaxHealth(float InHealth)
{
	MaxHealth = InHealth;
}

void UProject_157HealthComponent::AddHealth(float InHealth)
{
	if (InHealth + CurrentHealth < MaxHealth)
	{
		CurrentHealth += InHealth;
	}
	else
	{
		CurrentHealth = MaxHealth;
	}
}

void UProject_157HealthComponent::ReduceHealth(float InDamage, AActor* DamageCauser)
{
	if (CurrentHealth - InDamage > 0)
	{
		CurrentHealth -= InDamage;
	}
	else
	{
		CurrentHealth = 0;
		OnDieDelegate.Broadcast(CurrentHealth);
	}
	OnTakeDamageDelegate.Broadcast(InDamage, DamageCauser);
}
