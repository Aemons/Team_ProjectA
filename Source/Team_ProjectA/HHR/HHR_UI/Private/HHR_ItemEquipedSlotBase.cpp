// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ItemEquipedSlotBase.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_GameInstance.h"

void UHHR_ItemEquipedSlotBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	LoadPlayerArmorData();
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
	if(EqItemData.ItemImage)
	{
		FSlateBrush newBrush;
		newBrush.SetResourceObject(EqItemData.ItemImage);

		ItemIcon->SetBrush(newBrush);
	}

}

void UHHR_ItemEquipedSlotBase::LoadPlayerArmorData()
{
	UHHR_GameInstance* GI = Cast<UHHR_GameInstance>(GetWorld()->GetGameInstance());
	if(GI)
	{
		// GameInstance에 저장된 장착된 장비 가져오기
		switch(EqArmorType)
		{
		case EArmorType::Helmet:
			EqItemData = *GI->GetEqHelmetData();
			break;
		case EArmorType::Chest:
			EqItemData = *GI->GetEqChestData();
			break;
		case EArmorType::Pants:
			EqItemData = *GI->GetEqPantsData();
			break;
		case EArmorType::Boots:
			EqItemData = *GI->GetEqBootsData();
			break;
		default:
			break;
		}
		
	}
}
