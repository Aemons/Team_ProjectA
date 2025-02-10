// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_Inventory.h"

#include "Components/Button.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ButtonBase.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_InventoryDrawer.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ItemEquipedSlotBase.h"

void UHHR_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	// List에 넣기
	ItemSlotMap.Add(1, HelmetSlot);
	ItemSlotMap.Add(2, ChestSlot);
	ItemSlotMap.Add(3, PantsSlot);
	ItemSlotMap.Add(4, HandsSlot);
	ItemSlotMap.Add(5, BootsSlot);

	// 델리게이트에 바인딩
	for(TPair<int32, UHHR_ItemEquipedSlotBase*> itemSlot: ItemSlotMap)
	{
		(itemSlot.Value)->OnBtnClickMessage.AddDynamic(this, &UHHR_Inventory::OnUpdateEquipedSlot);
	}
	
	InventoryDrawer->OnPageSwitch.AddDynamic(this, &UHHR_Inventory::UpdateItemEqSlot);

	CloseBtn->GetButton()->OnClicked.AddDynamic(this, &UHHR_Inventory::Close);
	
}

void UHHR_Inventory::UpdateItemEqSlot(int32 ItemMenuIdx)
{
	// click 되어있는지 확인
	if(ItemSlotMap.Contains(SelectedSlotIdx))
	{
		// 선택되어 있으면 해제
		ItemSlotMap[SelectedSlotIdx]->Unselected();
	}

	// 현재꺼 선택
	if(ItemSlotMap.Contains(ItemMenuIdx))
	{
		ItemSlotMap[ItemMenuIdx]->Selected();
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

void UHHR_Inventory::Close()
{
	if(OnInventoryClose.IsBound())
	{
		OnInventoryClose.Execute();
	}
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


