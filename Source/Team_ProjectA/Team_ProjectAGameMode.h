// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Team_ProjectAGameMode.generated.h"

UCLASS(minimalapi)
class ATeam_ProjectAGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATeam_ProjectAGameMode();

protected:
	virtual void BeginPlay() override;



// UI Widget class 들
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI Widgets")
	TSubclassOf<UUserWidget> StartMenuClass;
	
	
};



