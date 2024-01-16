// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_157GameMode.h"
#include "Project_157Pawn.h"
#include "Project_157Hud.h"

AProject_157GameMode::AProject_157GameMode()
{
	DefaultPawnClass = AProject_157Pawn::StaticClass();
	HUDClass = AProject_157Hud::StaticClass();
}
