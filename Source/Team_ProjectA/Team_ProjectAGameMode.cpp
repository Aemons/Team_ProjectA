// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team_ProjectAGameMode.h"
#include "Team_ProjectACharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeam_ProjectAGameMode::ATeam_ProjectAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
