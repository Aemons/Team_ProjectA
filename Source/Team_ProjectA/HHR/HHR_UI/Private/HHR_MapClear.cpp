// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_MapClear.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_UIManager.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ButtonBase.h"

void UHHR_MapClear::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼에 바인딩
	GoOutMapBtn->GetButton()->OnClicked.AddDynamic(this, &UHHR_MapClear::OnGoOUtMap);
	ReChallengeBtn->GetButton()->OnClicked.AddDynamic(this, &UHHR_MapClear::OnReChallenge);

	// 생성과 동시에 anim 실행
	PlayAnimationForward(Fade);
}

void UHHR_MapClear::OnReChallenge()
{
	// 다시 도전 -> 맵 다시 로드
	UHHR_UIManager::GetUIManager()->SetGameOnlyMode();

	FName CurrentLevel = FName(GetWorld()->GetMapName());
	CurrentLevel = *CurrentLevel.ToString().RightChop(GetWorld()->StreamingLevelsPrefix.Len());

	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevel);
}

void UHHR_MapClear::OnGoOUtMap()
{
	UHHR_UIManager::GetUIManager()->SetGameOnlyMode();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ConceptMap"));
}
