// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_MapSelect.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_ButtonBase.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_MapSlotBase.h"

void UHHR_MapSelect::NativeConstruct()
{
	Super::NativeConstruct();

	// Button Binding
	BtnComp_Close->GetButton()->OnClicked.AddDynamic(this, &UHHR_MapSelect::OnClickCloseBtn);
	BtnComp_MapSelect->GetButton()->OnClicked.AddDynamic(this, &UHHR_MapSelect::OnClickMapSelectBtn);

	// TODO : 임시
	MapSlots.Add(MapComp_Map1);
	MapSlots.Add(MapComp_Map2);
	MapSlots.Add(MapComp_Map1_Test1);
	MapSlots.Add(MapComp_Map1_Test2);

	// array의 델리게이트 바인딩
	for(UHHR_MapSlotBase* slot : MapSlots)
	{
		slot->OnMapSlotClicked.BindUObject(this, &UHHR_MapSelect::MapClick);
	}

}

void UHHR_MapSelect::OnClickCloseBtn()
{
	// 현재 UI 닫기 && mouse 없애기 
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	RemoveFromParent();

	
}

void UHHR_MapSelect::OnClickMapSelectBtn()
{
	
	// 해당 맵으로 이동
	if(SelectedMap && !SelectedMap->LoadLevelName.IsEmpty())
	{
		FString Map = SelectedMap->LoadLevelName.ToString();
		UGameplayStatics::OpenLevel(GetWorld(), FName(*Map));
		
		// TODO : 마우스 설정 나중에 수정 
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	}
}

void UHHR_MapSelect::MapClick(UHHR_MapSlotBase* Clickedslot)
{
	// 현재 clicked 되어 있는 map 확인 후 상태 변경 selectedMap 변경
	UHHR_MapSlotBase* preClickedSlot = CheckClickedSlot();
	if(preClickedSlot)
	{
		// 있으면 변경
		preClickedSlot->SetSelectBorderHidden();
		preClickedSlot->SetIsCliked(false);
	}
	SelectedMap = Clickedslot;
	
}

UHHR_MapSlotBase* UHHR_MapSelect::CheckClickedSlot()
{
	// MapSlots Array에서 isclicked 되엉 있는 Map 보내기
	for(UHHR_MapSlotBase* slot : MapSlots)
	{
		if(slot->GetIsClicked())
		{
			return slot;
		}
	}
	return nullptr;
}
