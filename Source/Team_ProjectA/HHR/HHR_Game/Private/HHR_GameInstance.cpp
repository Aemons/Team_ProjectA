// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_GameInstance.h"

#include "Engine/DataTable.h"
#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_ItemBase.h"

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

	// Eq Item data list에 연결
	HelmetsList.Add(&EqHelmetData);
	AllItemsList.Add(&EqHelmetData);
	ChestsList.Add(&EqChestData);
	AllItemsList.Add(&EqChestData);
	PantsList.Add(&EqPantsData);
	AllItemsList.Add(&EqPantsData);
	BootsList.Add(&EqBootsData);
	AllItemsList.Add(&EqBootsData);
	
}

void UHHR_GameInstance::DropItems(FVector Location)
{
	// 몬스터의 위치를 받아서 그 해당 위치의 반경 500 정도에서 램덤으로 방어구 각각 1개씩 생성

	float zHeight = 50.f;
	float dis = 150.f;

	TArray<int32> RandomIdx;
	ShuffleIdx(RandomIdx, DTAllItemsList.Num(), 4);
	// 랜덤 생성
	for(int32 idx : RandomIdx)
	{
		FVector spawnLocation;
		spawnLocation.X = FMath::RandRange(Location.X - dis, Location.X + dis);
		spawnLocation.Y = FMath::RandRange(Location.Y - dis, Location.Y + dis);
		spawnLocation.Z = Location.Z + zHeight;
		
		FRotator spawnRotation;
		spawnRotation.Yaw = FMath::RandRange(-180.f, 180.f);

		// 생성 + data setting
		if(ItemClass)
		{
			AHHR_ItemBase* item  = GetWorld()->SpawnActor<AHHR_ItemBase>(ItemClass, spawnLocation, spawnRotation);
			item->SetItemData(DTAllItemsList[idx]);
			item->SetColor();
		}
	}



}

void UHHR_GameInstance::AddItem(FItemData* Data)
{
	// 아이템 추가
	
	// 이미 보유하고 있으면 pass
	if(FindItem(Data->ItemID)) return;
	
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
	AllItemsList.Add(Data);
}

void UHHR_GameInstance::LoadDataTable(class UDataTable* DataTable)
{
	// 테스트용 
	/*if(DataTable)
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
			DTAllItemsList.Add(Data);
		}
	}*/

	TArray<FItemData*> Rows;
	DataTable->GetAllRows<FItemData>( TEXT("Loading Data in GI"),Rows);

	for(FItemData* Data : Rows)
	{
		// 전체 list에도 넣어줌
		DTAllItemsList.Add(Data);
	}
	
}

FItemData* UHHR_GameInstance::FindItem(int32 ID)
{
	for(FItemData* Data : AllItemsList)
	{
		if(Data->ItemID == ID)
		{
			return Data;
		}
	}
	return nullptr;
}

void UHHR_GameInstance::ShuffleIdx(TArray<int32>& OutRandIdx, int32 ArrayMaxNum, int32 RandomNum)
{
	// 초기화
	for(int32 i = 0; i < ArrayMaxNum; ++i)
	{
		OutRandIdx.Add(i);
	}

	// shuffle
	for(int32 i = 0; i < OutRandIdx.Num(); ++i)
	{
		int32 swapIdx = FMath::RandRange(0, OutRandIdx.Num() - 1);
		OutRandIdx.Swap(i, swapIdx);
	}

	// 나머지 제거
	if(OutRandIdx.Num() >= RandomNum)
	{
		OutRandIdx.SetNum(RandomNum);
	}
	
}
