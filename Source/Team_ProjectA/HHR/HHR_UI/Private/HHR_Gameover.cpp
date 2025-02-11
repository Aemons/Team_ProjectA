// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_Gameover.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_UIManager.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ButtonBase.h"

void UHHR_Gameover::NativeConstruct()
{
	Super::NativeConstruct();

	// 델리게이트 바인딩
	RestartBtn->GetButton()->OnClicked.AddDynamic(this, &UHHR_Gameover::OnRestart);
	GameendBtn->GetButton()->OnClicked.AddDynamic(this, &UHHR_Gameover::OnGameEnd);
	
	// 생성되면 바로 anim 재생
	if(Fade)
	{
		PlayAnimationForward(Fade);
	}
}

void UHHR_Gameover::OnGameEnd()
{
	//UHHR_UIManager::GetUIManager()->SetGameOnlyMode();
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UHHR_Gameover::OnRestart()
{
	UHHR_UIManager::GetUIManager()->SetGameOnlyMode();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ConceptMap"));
}
