// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_InventoryPageBase.h"

#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotBase.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotTest.h"


void UHHR_InventoryPageBase::NativePreConstruct()
{
	Super::NativePreConstruct();


	// ItemSlot들 생성
	/*for(int32 i = 0; i < RowNum ; ++i)
	{
		for(int32 j = 0; j < ColumNum; ++j)
		{
			if(!ItemSlotClass) continue;

			UHHR_ItemSlotTest* itemSlot = NewObject<UHHR_ItemSlotTest>(this, ItemSlotClass);
			GridPanel->AddChild(itemSlot);
			itemSlot->SetVisibility(ESlateVisibility::Hidden);

			if(UUniformGridSlot* gridSlot = Cast<UUniformGridSlot>(itemSlot->Slot))
			{
				gridSlot->SetRow(i);
				gridSlot->SetColumn(j);
			}

			ItemSlotList.Add(itemSlot);
		}
	}

	// ItemSlotList를 통해서 visible 설정 & ItemData 적용
	for(int32 i = 0; i < HaveItemSlotList.Num(); ++i)
	{
		if(i < ItemSlotList.Num())
		{
			ItemSlotList[i]->SetVisibility(ESlateVisibility::Visible);

			// ItemData 적용
			if(i < ItemDataList.Num())
			{
				HaveItemSlotList[i]->UpdateItemData(&ItemDataList[i]);
			}
		}
	}*/



	
}

void UHHR_InventoryPageBase::NativeConstruct()
{
	Super::NativeConstruct();


	
}
