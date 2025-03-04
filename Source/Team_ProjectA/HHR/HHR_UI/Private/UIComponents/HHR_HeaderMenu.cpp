// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_HeaderMenu.h"

#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_HeaderButton.h"

void UHHR_HeaderMenu::NativeConstruct()
{
	Super::NativeConstruct();


	// Button들 버튼 리스트에 넣기
	MenuBtnList.Add(AllBtn);
	MenuBtnList.Add(HelmetBtn);
	MenuBtnList.Add(ChestBtn);
	MenuBtnList.Add(PantsBtn);
	MenuBtnList.Add(HandsBtn);
	MenuBtnList.Add(BootsBtn);

	//
	for(UHHR_HeaderButton* headerBtn : MenuBtnList)
	{
		//headerBtn->OnClickMessage.AddDynamic(this, &UHHR_HeaderMenu::OnMenuUpdate);
	}
	
}

void UHHR_HeaderMenu::OnMenuUpdate(int MenuIdx)
{
	// TODO : click 되어 있으면 그것들 해제 

	int32 findIdx = FindClickedIndex();
	if(findIdx >= 0 && findIdx < MenuBtnList.Num())
	{
		// 선택되어 있는 거 찾으면 그거 선택 해제
		MenuBtnList[findIdx]->bIsSelected = false;
		MenuBtnList[findIdx]->OnUnSelected();
	}

	// click 한 거 업뎃
	//MenuBtnList[MenuIdx]->SetIsSelected(true);
	MenuBtnList[MenuIdx]->bIsSelected = true;
	MenuBtnList[MenuIdx]->OnSelected();
	
}

int32 UHHR_HeaderMenu::FindClickedIndex()
{
	for(int32 i = 0; i < MenuBtnList.Num(); ++i)
	{
		if(MenuBtnList[i]->bIsSelected)
		{
			return i;
		}
	}
	// 업으면 -1 반환
	return -1;
}
