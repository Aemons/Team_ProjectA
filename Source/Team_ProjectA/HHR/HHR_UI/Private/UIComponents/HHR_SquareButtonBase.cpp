// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_SquareButtonBase.h"

#include "Components/TextBlock.h"

void UHHR_SquareButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	// 값 할당
	BtnText->SetText(Text);
}
