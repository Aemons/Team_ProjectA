// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team_ProjectA : ModuleRules
{
	public Team_ProjectA(ReadOnlyTargetRules Target) : base(Target)
	{
		
		PublicDependencyModuleNames.AddRange(new string[]
        	{
        		"Core",
        		"CoreUObject",
        		"Engine",
        		"InputCore",
        		"EnhancedInput",
        		"HeadMountedDisplay",
        		"AIModule",
        		"GameplayTasks",
        		"NavigationSystem",
		        "LevelSequence",
		        "MovieScene",
		        "UMG"
        	});
		
		// SOS Using LevelSequnce
		////////////////////////////////////////////////////////////////////////////////////////////

		PrivateDependencyModuleNames.AddRange(new string[] { "LevelSequence", "Niagara", "NiagaraAnimNotifies" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		////////////////////////////////////////////////////////////////////////////////////////////

		
		//JHS Public/Private ��� �߰�
		        "UMG",
		        "Slate",
		        "SlateCore",
                "Niagara"
        	});
		
		//JHS Public/Private
		////////////////////////////////////////////////////////////////////////////////////////////
        PublicIncludePaths.AddRange(new string[] 
        {
            "Team_ProjectA/JHS/JHS_Global/Public", 
            "Team_ProjectA/JHS/JHS_Anim/Public",
            "Team_ProjectA/JHS/JHS_Player/Public",
            "Team_ProjectA/JHS/JHS_Component/Public",
            "Team_ProjectA/JHS/JHS_Weapon/Public",
            "Team_ProjectA/JHS/JHS_Notify/Public",
            "Team_ProjectA/JHS/JHS_Actions/Public"
        });
 
        PrivateIncludePaths.AddRange(new string[] 
        {
            "Team_ProjectA/JHS/JHS_Global/Private",
            "Team_ProjectA/JHS/JHS_Player/Private",
            "Team_ProjectA/JHS/JHS_Anim/Private",
            "Team_ProjectA/JHS/JHS_Component/Private",
            "Team_ProjectA/JHS/JHS_Weapon/Private",
            "Team_ProjectA/JHS/JHS_Notify/Private",
            "Team_ProjectA/JHS/JHS_Actions/Private"
        });
		////////////////////////////////////////////////////////////////////////////////////////////

    }
}