// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team_ProjectAGameMode.h"
#include "HHR/HHR_UI/Public/HHR_UIManager.h"
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

void ATeam_ProjectAGameMode::BeginPlay()
{
	// 레벨이 로드될때마다 호출 
	Super::BeginPlay();

	// UIManager 생성
	//UHHR_UIManager* UIManager = NewObject<UHHR_UIManager>();
	//UIManager->Init(GetWorld());
	//UIManager->CreateUI(StartMenuClass);
	// 마우스
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
