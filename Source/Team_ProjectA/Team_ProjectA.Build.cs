// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team_ProjectA : ModuleRules
{
	public Team_ProjectA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
    }
}
