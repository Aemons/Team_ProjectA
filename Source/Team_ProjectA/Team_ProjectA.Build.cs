// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team_ProjectA : ModuleRules
{
	public Team_ProjectA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		//JHS Public/Private 경로 추가
		////////////////////////////////////////////////////////////////////////////////////////////
        PublicIncludePaths.AddRange(new string[] 
        {
            "Team_ProjectA/JHS/JHS_Global/Public", 
            "Team_ProjectA/JHS/JHS_Anim/Public",
            "Team_ProjectA/JHS/JHS_Player/Public",
            "Team_ProjectA/JHS/JHS_Component/Public",
            "Team_ProjectA/JHS/JHS_Weapon/Public"
        });
 
        PrivateIncludePaths.AddRange(new string[] 
        {
            "Team_ProjectA/JHS/JHS_Global/Private",
            "Team_ProjectA/JHS/JHS_Player/Private",
            "Team_ProjectA/JHS/JHS_Anim/Private",
            "Team_ProjectA/JHS/JHS_Component/Private",
            "Team_ProjectA/JHS/JHS_Weapon/Private"
        });
		////////////////////////////////////////////////////////////////////////////////////////////

    }
}