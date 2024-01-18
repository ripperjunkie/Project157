// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157HeroItem.h"

#include "Components/AudioComponent.h"


// Sets default values
AProject_157HeroItem::AProject_157HeroItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Static Mesh Comp"));
	StaticMeshComp->SetupAttachment(RootComponent);
	
	ShootAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot Audio Comp"));
	ShootAudioComp->SetupAttachment(StaticMeshComp);
	ShootAudioComp->bAutoActivate = false;
	
	ReloadAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Reload Audio Comp"));
	ReloadAudioComp->SetupAttachment(StaticMeshComp);
	ReloadAudioComp->bAutoActivate = false;
}



// Called when the game starts or when spawned
void AProject_157HeroItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProject_157HeroItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
