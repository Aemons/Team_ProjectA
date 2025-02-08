// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_GameInstance.h"

#include "Engine/DataTable.h"

void UHHR_GameInstance::Init()
{
	Super::Init();

	// Data Table 가져오기
	FString DTPath = TEXT("/Script/Engine.DataTable'/Game/00_Project/HHR/HHR_Data/DT_ItemDataTable.DT_ItemDataTable'");
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DTPath));
	if(DataTable)
	{
		LoadDataTable(DataTable);
	}
	
}

void UHHR_GameInstance::AddItem(FItemData* Data)
{
	// 아이템 추가
	switch (Data->ArmorType)
	{
	case EArmorType::Helmet:
		HelmetsList.Add(Data);
		break;
	case EArmorType::Chest:
		ChestsList.Add(Data);
		break;
	case EArmorType::Pants:
		PantsList.Add(Data);
		break;
	case EArmorType::Boots:
		BootsList.Add(Data);
		break;
	default:
		break;
	}
}

void UHHR_GameInstance::LoadDataTable(class UDataTable* DataTable)
{
	if(DataTable)
	{
		// 디버깅 정보를 제공하기 위한 문자열 제공 필요
		TArray<FItemData*> Rows;
		DataTable->GetAllRows<FItemData>( TEXT("Loading Data in GI"),Rows);

		for(FItemData* Data : Rows)
		{
			switch(Data->ArmorType)
			{
				case EArmorType::Helmet:
					HelmetsList.Add(Data);
					break;
				case EArmorType::Chest:
					ChestsList.Add(Data);
					break;
				case EArmorType::Pants:
					PantsList.Add(Data);
					break;
				case EArmorType::Boots:
					BootsList.Add(Data);
					break;
				default:
					break;
			}
			// 전체 list에도 넣어줌
			AllItemsList.Add(Data);	
		}

		;;
	}
	
}
