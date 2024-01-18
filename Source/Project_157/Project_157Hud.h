// Copyright (c) 2024 @ Rafael Zagolin

#pragma once
#include "GameFramework/HUD.h"
#include "Project_157Hud.generated.h"


UCLASS(config = Game)
class AProject_157Hud : public AHUD
{
	GENERATED_BODY()

public:
	AProject_157Hud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
