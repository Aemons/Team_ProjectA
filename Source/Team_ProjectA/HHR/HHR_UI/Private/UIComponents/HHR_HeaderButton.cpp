// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_HeaderButton.h"

#include "Components/Border.h"

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
}
