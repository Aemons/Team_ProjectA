// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_HeaderButton.h"

#include "Components/Border.h"
#include "Components/Button.h"

void UHHR_HeaderButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Editable 값들 세팅

	if(IconImage)
	{
		FSlateBrush newBrush;
		newBrush.SetResourceObject(IconImage);
		newBrush.TintColor = IconColor;
		IconBorder->SetBrush(newBrush);
	}

	if(bIsSelected)
	{
		OnSelected();
	}
}

void UHHR_HeaderButton::NativeConstruct()
{
	Super::NativeConstruct();

	// 델리게이트 바인딩
	HitBox->OnClicked.AddDynamic(this, &UHHR_HeaderButton::OnClicked);
}

void UHHR_HeaderButton::OnClicked()
{
	
	// click 메세지 전송
	if(OnClickMessage.IsBound())
	{
		OnClickMessage.Broadcast(MenuIndex);
	}


	
}
