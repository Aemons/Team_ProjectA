// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotTest.h"

#include "JHS_C_Player.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_InventoryComponent.h"

void UHHR_ItemSlotTest::NativePreConstruct()
{
	Super::NativePreConstruct();

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

	// TODO: click시 옷 교환 + click 내용 반영
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
