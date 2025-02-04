// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotTest.h"

#include "Components/Border.h"
#include "Components/Button.h"

void UHHR_ItemSlotTest::NativePreConstruct()
{
	Super::NativePreConstruct();

	// hidden이면 업뎃 안함
	UpdateItemData(&ItemData);

}

void UHHR_ItemSlotTest::NativeConstruct()
{
	Super::NativeConstruct();

	// 바인딩
	ItemButton->OnClicked.AddDynamic(this, &UHHR_ItemSlotTest::OnClicked);
	ItemButton->OnHovered.AddDynamic(this, &UHHR_ItemSlotTest::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UHHR_ItemSlotTest::OnUnHovered);
}

void UHHR_ItemSlotTest::OnHovered()
{
	if(HoverEffect)
	{
		PlayAnimationForward(HoverEffect);
	}
}

void UHHR_ItemSlotTest::OnUnHovered()
{
	if(HoverEffect)
	{
		PlayAnimationReverse(HoverEffect);
	}
}

void UHHR_ItemSlotTest::OnClicked()
{
	SelectedBorder->SetVisibility(ESlateVisibility::Visible);

	// TODO: click시 옷 교환
	

}

void UHHR_ItemSlotTest::UpdateItemData(FItemData* Data)
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
