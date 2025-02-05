// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_Inventory.h"

#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_InventoryDrawer.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ItemEquipedSlotBase.h"

void UHHR_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	// List에 넣기
	ItemSlotList.Add(HelmetSlot);
	ItemSlotList.Add(ChestSlot);
	ItemSlotList.Add(PantsSlot);
	ItemSlotList.Add(HandsSlot);
	ItemSlotList.Add(BootsSlot);

	// 델리게이트에 바인딩
	for(UHHR_ItemEquipedSlotBase* itemSlot: ItemSlotList)
	{
		itemSlot->OnBtnClickMessage.AddDynamic(this, &UHHR_Inventory::OnUpdateEquipedSlot);
	}
	InventoryDrawer->OnPageSwitch.AddDynamic(this, &UHHR_Inventory::UpdateItemEqSlot);
	
}

void UHHR_Inventory::UpdateItemEqSlot(int32 ItemMenuIdx)
{
	// click 되어있는지 확인
	if(SelectedSlotIdx >= 0 && SelectedSlotIdx < ItemSlotList.Num())
	{
		// 선택되어 있으면 해제
		ItemSlotList[SelectedSlotIdx]->Unselected();
	}
	
	// 현재꺼 선택
	if(ItemMenuIdx >= 0 && ItemMenuIdx < ItemSlotList.Num())
	{
		ItemSlotList[ItemMenuIdx]->Selected();
		SelectedSlotIdx = ItemMenuIdx;
	}
}

void UHHR_Inventory::OnUpdateEquipedSlot(int32 ItemMenuIdx)
{
	// click 되어있는지 확인
	UpdateItemEqSlot(ItemMenuIdx);

	// TODO : Drawer 업뎃 
	InventoryDrawer->UpdateDrawer(ItemMenuIdx);
}

void UHHR_Inventory::ChangeHelemtSlot(FItemData* Data)
{
	HelmetSlot->EqItemData = *Data;
	HelmetSlot->UpdateData();
}

void UHHR_Inventory::ChangeChestSlot(FItemData* Data)
{
	ChestSlot->EqItemData = *Data;
	ChestSlot->UpdateData();
}

void UHHR_Inventory::ChangePantsSlot(FItemData* Data)
{
	PantsSlot->EqItemData = *Data;
	PantsSlot->UpdateData();
}

void UHHR_Inventory::ChangeBootsSlot(FItemData* Data)
{
	BootsSlot->EqItemData = *Data;
	BootsSlot->UpdateData();
}


