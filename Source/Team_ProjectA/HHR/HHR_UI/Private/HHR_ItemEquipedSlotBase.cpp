// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ItemEquipedSlotBase.h"

#include "Components/Border.h"
#include "Components/Button.h"

void UHHR_ItemEquipedSlotBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateData();
	if(bIsSelected)
	{
		Selected();
	}

}

void UHHR_ItemEquipedSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	// Button에 바인딩
	ItemButton->OnHovered.AddDynamic(this, &UHHR_ItemEquipedSlotBase::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UHHR_ItemEquipedSlotBase::OnUnHovered);
	ItemButton->OnClicked.AddDynamic(this, &UHHR_ItemEquipedSlotBase::OnClicked);
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

void UHHR_ItemEquipedSlotBase::OnClicked()
{
	// Message 전송
	OnBtnClickMessage.Broadcast(ItemMenuIdx);
	
}

void UHHR_ItemEquipedSlotBase::Selected()
{
	bIsSelected = true;
	SelectedBorder->SetVisibility(ESlateVisibility::Visible);
}

void UHHR_ItemEquipedSlotBase::Unselected()
{
	bIsSelected = false;
	SelectedBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UHHR_ItemEquipedSlotBase::UpdateData()
{
	if(ItemData.ItemImage)
	{
		FSlateBrush newBrush;
		newBrush.SetResourceObject(ItemData.ItemImage);

		ItemIcon->SetBrush(newBrush);
	}

}
