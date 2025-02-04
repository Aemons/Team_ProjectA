// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotBase.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"

void UHHR_ItemSlotBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Data 업뎃
	// 이미지 업뎃
	UpdateItemData(&ItemData);
	
}

void UHHR_ItemSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	// 바인딩
	ItemButton->OnClicked.AddDynamic(this, &UHHR_ItemSlotBase::OnClicked);
	ItemButton->OnHovered.AddDynamic(this, &UHHR_ItemSlotBase::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UHHR_ItemSlotBase::OnUnHovered);
}

void UHHR_ItemSlotBase::OnHovered()
{
	if(HoverEffect)
	{
		PlayAnimationForward(HoverEffect);
	}
}

void UHHR_ItemSlotBase::OnUnHovered()
{
	if(HoverEffect)
	{
		PlayAnimationReverse(HoverEffect);
	}
}

void UHHR_ItemSlotBase::OnClicked()
{
	// TODO : InventoryDialog visible 보이게 하기 + Data 업뎃
	
	SelectedBorder->SetVisibility(ESlateVisibility::Visible);
}

void UHHR_ItemSlotBase::UpdateItemData(FItemData* Data)
{
	if(Data->ItemImage)
	{
		FSlateBrush newBrush;
		newBrush.SetResourceObject(Data->ItemImage);

		if(ItemImage)
		{
			ItemImage->SetBrush(newBrush);
		}
	}

}
