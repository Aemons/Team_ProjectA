// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_MonsterHP.h"

#include "Components/TextBlock.h"



void UHHR_MonsterHP::NativePreConstruct()
{
	Super::NativePreConstruct();

	// 값 세팅 
	MonsterTextBlock->SetText(MonsterName);
}

void UHHR_MonsterHP::NativeConstruct()
{
	Super::NativeConstruct();


}

float UHHR_MonsterHP::GetHPProgressBar() const
{
	if(OnHPGetPercent.IsBound())
	{
		return OnHPGetPercent.Execute();
	}
	return 0.f;
}