// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_MapSlotBase.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UHHR_MapSlotBase::NativePreConstruct()
{
	Super::NativePreConstruct();


	// TODO : 데이터 테이블을 통해서 값 세팅하도록 수정 -> 유지보수 
	// 동적으로 받은 값들 세팅
	MapNameText->SetText(MapName);
	MapLevelText->SetText(LevelText);
	MapPointText->SetText(PointText);
	MapDescriptionText->SetText(MapDescription);
	
	if(Image)
	{
		// !! FSlateBrush 사용할려면 Build.cs 파일에서 Slate, SltateCore를 추가해줘야함...
		FSlateBrush newBrush;
		newBrush.SetResourceObject(Image);
		MapImage->SetBrush(newBrush);
	}
}

void UHHR_MapSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Border visibile setting
	AnimBorder->SetVisibility(ESlateVisibility::Hidden);
	SelectBorder->SetVisibility(ESlateVisibility::Hidden);
	
	// Button Binding
	HitBox->OnClicked.AddDynamic(this, &UHHR_MapSlotBase::OnClick);
	HitBox->OnHovered.AddDynamic(this, &UHHR_MapSlotBase::OnHover);
	HitBox->OnUnhovered.AddDynamic(this, &UHHR_MapSlotBase::OnUnHover);

	
}

void UHHR_MapSlotBase::OnHover()
{
	// Animation 재생
	if(!bIsClicked && Hover)
	{
		PlayAnimationForward(Hover);
	}
}

void UHHR_MapSlotBase::OnUnHover()
{
	// Animaiton 재생
	if(!bIsClicked && Hover)
	{
		PlayAnimationReverse(Hover);
	}

}

void UHHR_MapSlotBase::OnClick()
{

	OnMapSlotClicked.Execute(this);

	if(!bIsClicked)
	{
		bIsClicked = true;
		// Material 변경
		SelectBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		bIsClicked = false;
		// Material 변경
		SelectBorder->SetVisibility(ESlateVisibility::Hidden);
	}

}
