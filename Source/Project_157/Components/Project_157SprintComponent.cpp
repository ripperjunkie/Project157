// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157SprintComponent.h"

#include "Project_157AimComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project_157/Characters/Project_157Player.h"


// Sets default values for this component's properties
UProject_157SprintComponent::UProject_157SprintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProject_157SprintComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UProject_157SprintComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UProject_157SprintComponent::StartSprint()
{
	PlayerRef->ResetState(EProject_157ActionState::Crouching);
	PlayerRef->ResetState(EProject_157ActionState::Aiming);
	PlayerRef->SetCurrentState(EProject_157ActionState::Sprinting);
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef-> GetMovementSettings().RunWalkSpeed;
	PlayerRef->GetAimComponent()->ToggleAim(false);
}

void UProject_157SprintComponent::StopSprint()
{	
	PlayerRef->ResetState(EProject_157ActionState::Sprinting);
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef-> GetDefaultMovementSettings().MaxWalkSpeed;
}

