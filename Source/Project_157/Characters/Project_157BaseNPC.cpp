#include "Project_157BaseNPC.h"

#include "Project_157/Components/Project_157HealthComponent.h"


DEFINE_LOG_CATEGORY(LogProject_157BaseEnemy);

// Sets default values
AProject_157BaseNPC::AProject_157BaseNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Creating inventory component by default */
	HealthComponent = CreateDefaultSubobject<UProject_157HealthComponent>(TEXT("Health Component"));
	HealthComponent->SetMaxHealth(100);

}

// Called when the game starts or when spawned
void AProject_157BaseNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProject_157BaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AProject_157BaseNPC::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	HealthComponent->ReduceHealth(DamageAmount, DamageCauser);
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);	
}

void AProject_157BaseNPC::TakeDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, FName BoneName)
{
	IProject_157CharacterInterface::TakeDamage_Implementation(DamageAmount, DamageEvent, EventInstigator, DamageCauser, BoneName);

	// TODO: Filter damage
	this->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


/* Override it by blueprint.*/
void AProject_157BaseNPC::OnShoot_Implementation(FVector& _MuzzleLocation)
{
	IProject_157CharacterInterface::OnShoot_Implementation(_MuzzleLocation);
}

/* Override it by blueprint.*/
void AProject_157BaseNPC::OnShoot_Camera_Implementation(FVector& _MuzzleLocation, FVector& Direction)
{
	IProject_157CharacterInterface::OnShoot_Camera_Implementation(_MuzzleLocation, Direction);
}


