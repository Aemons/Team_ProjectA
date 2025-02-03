// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_InventoryDrawer.h"

#include "Components/WidgetSwitcher.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_HeaderButton.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_HeaderMenu.h"

void UHHR_InventoryDrawer::NativeConstruct()
{
	Super::NativeConstruct();

	// 델리게이트에 바인딩
	for(UHHR_HeaderButton* headerBtn : HeaderMenu->MenuBtnList)
	{
		if(headerBtn)
		{
			headerBtn->OnClickMessage.AddDynamic(this, &UHHR_InventoryDrawer::OnSwitchPage);
		}
	}

	
}

void UHHR_InventoryDrawer::OnSwitchPage(int32 PageIdx)
{

	// Header 업뎃 -> 이러면 Header Menu에서 바인딩 안해줘도 됨
	UpdateDrawer(PageIdx);

	// TODO : Inventory도 업뎃
	if(OnPageSwitch.IsBound())
	{
		OnPageSwitch.Broadcast(PageIdx);
	}

}

void UHHR_InventoryDrawer::UpdateDrawer(int32 PageIdx)
{
	HeaderMenu->OnMenuUpdate(PageIdx);

	if(PageIdx <= PageSwitcher->GetNumWidgets())
	{
		PageSwitcher->SetActiveWidgetIndex(PageIdx);
	}
}
