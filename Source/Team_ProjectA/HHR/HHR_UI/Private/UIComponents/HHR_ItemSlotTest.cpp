// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotTest.h"

#include "JHS_C_Player.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_GameInstance.h"
#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_InventoryComponent.h"

void UHHR_ItemSlotTest::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	LoadPlayerSelected();

	UpdateItemData(&ItemData);
	if(bIsSelected)
	{
		Selected();
	}


}

void UHHR_ItemSlotTest::NativeConstruct()
{
	Super::NativeConstruct();

	// 바인딩
	ItemButton->OnClicked.AddDynamic(this, &UHHR_ItemSlotTest::OnClicked);
	ItemButton->OnHovered.AddDynamic(this, &UHHR_ItemSlotTest::OnHovered);
	ItemButton->OnUnhovered.AddDynamic(this, &UHHR_ItemSlotTest::OnUnHovered);

	// 
	AJHS_C_Player* player = Cast<AJHS_C_Player>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(player)
	{
		UHHR_InventoryComponent* invenComp =  player->GetInventoryComp();
		if(invenComp)
		{
			OnItemChanged.AddDynamic(invenComp, &UHHR_InventoryComponent::ChangeArmor);
		}
	}

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
	//Selected();

	// TODO: click시 옷 교환(InventoryComp) + click 내용 반영(Page)
	if(OnItemChanged.IsBound())
	{
		OnItemChanged.Broadcast(this);
	}
	

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

void UHHR_ItemSlotTest::Selected()
{
	bIsSelected = true;
	SelectedBorder->SetVisibility(ESlateVisibility::Visible);
}

void UHHR_ItemSlotTest::UnSelected()
{
	bIsSelected = false;
	SelectedBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UHHR_ItemSlotTest::LoadPlayerSelected()
{
	UHHR_GameInstance* GI = Cast<UHHR_GameInstance>(GetWorld()->GetGameInstance());
	if(!GI) return;

	// GameInstance의 장착되어 있는 아이템이랑 비교해서 장착된 거 click set
	switch(ItemData.ArmorType)
	{
	case EArmorType::Helmet:
		if(GI->GetEqHelmetData()->ItemID ==  ItemData.ItemID)
		{
			bIsSelected = true;
		}
		break;
	case EArmorType::Chest:
		if(GI->GetEqChestData()->ItemID ==  ItemData.ItemID)
		{
			bIsSelected = true;
		}
		break;
	case EArmorType::Pants:
		if(GI->GetEqPantsData()->ItemID ==  ItemData.ItemID)
		{
			bIsSelected = true;
		}
		break;
	case EArmorType::Boots:
		if(GI->GetEqBootsData()->ItemID ==  ItemData.ItemID)
		{
			bIsSelected = true;
		}
		break;
	default:
		break;
		
	}
}














