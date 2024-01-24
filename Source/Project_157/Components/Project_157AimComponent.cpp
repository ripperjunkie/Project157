// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157AimComponent.h"

#include "Project_157SprintComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Project_157/Characters/Project_157Player.h"


// Sets default values for this component's properties
UProject_157AimComponent::UProject_157AimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UProject_157AimComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UProject_157AimComponent::StartAim()
{
	// start aiming	
	/* Check if character has weapon equipped. */	
	if(!PlayerRef->CheckState(EProject_157ActionState::ItemEquipped))
		return;
	
	ToggleAim(true);
	PlayerRef->SetCurrentState(EProject_157ActionState::Aiming);
	PlayerRef->ResetState(EProject_157ActionState::Sprinting);
	PlayerRef->GetSprintComponent()->StopSprint();
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef->GetMovementSettings().AimWalkSpeed;
}

void UProject_157AimComponent::StopAim()
{
	// stop aiming
	if (PlayerRef->CheckState(EProject_157ActionState::Aiming))
	{
		PlayerRef->ResetState(EProject_157ActionState::Aiming);
		ToggleAim(false);
		
		if(!PlayerRef->CheckState(EProject_157ActionState::Crouching))
			PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef->GetDefaultMovementSettings().MaxWalkSpeed;
	}
}

void UProject_157AimComponent::ToggleAim(bool aiming)
{
	PlayerRef->GetCameraComponent()->FieldOfView = aiming ?  PlayerRef->GetPlayerData().AimFOV : PlayerRef->GetPlayerData().DefaultFOV;
	PlayerRef->GetCharacterMovement()->bOrientRotationToMovement = !aiming;
	PlayerRef->bUseControllerRotationYaw = aiming;
	PlayerRef->GetSpringArmComponent()->TargetArmLength = aiming ?  PlayerRef->GetPlayerData().AimArmLength : PlayerRef->GetPlayerData().DefaultArmLength;
}