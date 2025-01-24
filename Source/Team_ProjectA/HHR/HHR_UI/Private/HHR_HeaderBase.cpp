// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_HeaderBase.h"

#include "Components/TextBlock.h"

void UHHR_HeaderBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Editable 변수 내용 적용
	if(HeaderText)
	{
		HeaderText->SetText(Text);
	}
}
