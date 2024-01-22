// Copyright (c) 2024 @ Rafael Zagolin


#include "Project_157PlayerSharedAnimInstance.h"
#include "Project_157/Interfaces/Project_157CharacterAnimInterface.h"


void UProject_157PlayerSharedAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	PawnOwner = TryGetPawnOwner();

	if(!PawnOwner)
		return;

	if(const IProject_157CharacterAnimInterface* charAnimInterface = Cast<IProject_157CharacterAnimInterface>(PawnOwner))
	{
		GroundSpeed = charAnimInterface->Execute_GetGroundSpeed(PawnOwner);
		GetCharacterState = (int32)charAnimInterface->Execute_GetCharacterState(PawnOwner) + 1;
		GetEquippedWeapon = (int32)charAnimInterface->Execute_GetCurrentEquippedWeapon(PawnOwner) + 1;
		bAiming = charAnimInterface->Execute_GetCheckState(PawnOwner, EProject_157ActionState::Aiming);
		GetLookAngle = FVector2D(charAnimInterface->Execute_GetLookForwardAngle(PawnOwner), charAnimInterface->Execute_GetLookUpAngle(PawnOwner));
	}
}
