// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_StartMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ButtonBase.h"

void UHHR_StartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BtnComp_GameEnd->GetButton()->OnClicked.AddDynamic(this, &UHHR_StartMenu::OnQuitGame);
	
}

void UHHR_StartMenu::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
