// Copyright (c) 2024 @ Rafael Zagolin

using UnrealBuildTool;
using System.Collections.Generic;

public class Project_157Target : TargetRules
{
	public Project_157Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Project_157");
	}
}
