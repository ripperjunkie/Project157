// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_157GameMode.h"
#include "Vehicles/Project_157BaseVehicle.h"
#include "Project_157Hud.h"

AProject_157GameMode::AProject_157GameMode()
{
	DefaultPawnClass = AProject_157BaseVehicle::StaticClass();
	HUDClass = AProject_157Hud::StaticClass();
}
