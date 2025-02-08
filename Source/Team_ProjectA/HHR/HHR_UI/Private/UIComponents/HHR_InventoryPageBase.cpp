// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_InventoryPageBase.h"

#include "Components/GridSlot.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_GameInstance.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotBase.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotTest.h"


void UHHR_InventoryPageBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	GetInventoryData();
	LoadItemData();

	
}

void UHHR_InventoryPageBase::NativeConstruct()
{
	Super::NativeConstruct();


	// 바인딩
	for(UHHR_ItemSlotTest* itemSlot : ItemSlotList)
	{
		itemSlot->OnItemChanged.AddDynamic(this, &UHHR_InventoryPageBase::UpdateSlotClick);
	}
	
}

void UHHR_InventoryPageBase::UpdateSlotClick(UHHR_ItemSlotTest* ClickItem)
{
	// itemslot 전체 탐색해서 selected 되어 있는거 탐색후 찾으면 selected 해제 + click된거 selected

	for(UHHR_ItemSlotTest* slot : ItemSlotList)
	{
		if(slot->ItemData.ArmorType == ClickItem->ItemData.ArmorType)
		{
			if(slot->bIsSelected)
			{
				slot->ChangeUnSelected();
			}
		}
	}

	ClickItem->ChangeSelected();
	
}

void UHHR_InventoryPageBase::GetInventoryData()
{
	UHHR_GameInstance* GI = Cast<UHHR_GameInstance>(GetGameInstance());
	if(!GI) return;

	switch (PageType)
	{
	case EPageType::AllPage:
		{
			InventoryData = GI->GetAllItemList();
			break;
		}
	case EPageType::HelmetPage:
		{
			InventoryData = GI->GetHelmetsList();
			break;
		}
	case EPageType::ChestPage:
		{
			InventoryData = GI->GetChestsList();
			break;
		}
	case EPageType::PantsPage:
		{
			InventoryData = GI->GetPantsList();
			break;
		}
	case EPageType::BootsPage:
		{
			InventoryData = GI->GetBootsList();
			break;
		}
	case EPageType::HandsPage:
		break;
	default:
		break;
	}
	
}

void UHHR_InventoryPageBase::LoadItemData()
{
	
	for(int32 i = 0; i < InventoryData.Num(); i++)
	{
		UHHR_ItemSlotTest* newItemSlot = NewObject<UHHR_ItemSlotTest>(this, ItemSlotClass);
		if(newItemSlot)
		{
			newItemSlot->SetData(InventoryData[i]);
			ItemSlotList.Add(newItemSlot);

			// Slot Setting
			UUniformGridSlot* slot = GridPanel->AddChildToUniformGrid(newItemSlot);
			int r = i / ColumNum;
			int c = i % ColumNum;
			slot->SetRow(r);
			slot->SetColumn(c);
		}
	}

}











