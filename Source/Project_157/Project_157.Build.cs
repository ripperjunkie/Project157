// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_157 : ModuleRules
{
	public Project_157(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysXVehicles", "HeadMountedDisplay", "ImGui" });

		PublicDefinitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
