// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team_ProjectA : ModuleRules
{
	public Team_ProjectA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
        		"NavigationSystem"
        	});
		
		//JHS Public/Private ��� �߰�
		////////////////////////////////////////////////////////////////////////////////////////////
        PublicIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Global/Public"});
        PublicIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Anim/Public"});
        PublicIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Player/Public"});
        PublicIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Component/Public"});

        PrivateIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Global/Private"});
        PrivateIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Player/Private"});
        PrivateIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Anim/Private"});
        PrivateIncludePaths.AddRange(new string[] {"Team_ProjectA/JHS/JHS_Component/Private"});



		////////////////////////////////////////////////////////////////////////////////////////////

    }
}