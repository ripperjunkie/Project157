// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157PlayerSharedAnimInstance.h"
#include "Project_157/Interfaces/Project_157CharacterAnimInterface.h"


void UProject_157PlayerSharedAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	PawnOwner = TryGetPawnOwner();

	if(!PawnOwner)
		return;

	if(const IProject_157CharacterAnimInterface* itemInterface = Cast<IProject_157CharacterAnimInterface>(PawnOwner))
	{
		GroundSpeed = itemInterface->Execute_GetGroundSpeed(PawnOwner);
		GetCharacterState = (int32)itemInterface->Execute_GetCharacterState(PawnOwner) + 1;
		GetEquippedWeapon = (int32)itemInterface->Execute_GetCurrentEquippedWeapon(PawnOwner) + 1;
		bAiming = itemInterface->Execute_GetCheckState(PawnOwner, EProject_157ActionState::Aiming);
	}
}
