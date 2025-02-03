// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ItemEquipedSlotBase.h"

#include "Components/Button.h"

void UHHR_ItemEquipedSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Button에 바인딩
	ItemButton->OnHovered.AddDynamic(this, &UHHR_ItemEquipedSlotBase::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UHHR_ItemEquipedSlotBase::OnUnHovered);
}

void UHHR_ItemEquipedSlotBase::OnHovered()
{
	if(HoverEffect)
	{
		PlayAnimationForward(HoverEffect);
	}
}

void UHHR_ItemEquipedSlotBase::OnUnHovered()
{
	if(HoverEffect)
	{
		PlayAnimationReverse(HoverEffect);
	}
}
