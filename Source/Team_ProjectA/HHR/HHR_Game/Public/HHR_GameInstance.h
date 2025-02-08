// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
#include "HHR_GameInstance.generated.h"

/** GameInstance
 * 전역 데이터 관리 
 * 
 */


struct FItemData;

UCLASS()
class TEAM_PROJECTA_API UHHR_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	// 내가 장착하고 있는 장비, 가지고 있는 장비 저장

	// !가지고 있는 장비 추가 (삭제), get


//////////////////////////////////////////////////////////////////////////////
// ** FORCEINLINE 함수 **
public:
	// * Eq Item *
	FORCEINLINE FItemData* GetEqHelmetData() { return &EqHelmetData; }
	FORCEINLINE FItemData* GetEqChestData() { return &EqChestData; }
	FORCEINLINE FItemData* GetEqPantsData() { return &EqPantsData; }
	FORCEINLINE FItemData* GetEqBootsData() { return &EqBootsData; }

	FORCEINLINE void SetEqHelmetData(const FItemData* Data) { EqHelmetData = *Data; }
	FORCEINLINE void SetEqChestData(const FItemData* Data) { EqChestData = *Data; }
	FORCEINLINE void SetEqPantsData(const FItemData* Data) { EqPantsData = *Data; }
	FORCEINLINE void SetEqBootsData(const FItemData* Data) { EqBootsData = *Data; }

	// * Have Item *
	// 읽기 전용 리스트 반환 
	FORCEINLINE TArray<FItemData*>& GetHelmetsList() { return HelmetsList;}
	FORCEINLINE TArray<FItemData*>& GetChestsList() { return ChestsList; }
	FORCEINLINE TArray<FItemData*>& GetPantsList() { return PantsList;}
	FORCEINLINE TArray<FItemData*>& GetBootsList() { return BootsList;}
	FORCEINLINE TArray<FItemData*>& GetAllItemList() { return AllItemsList;}
	

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:
	// 그냥 Id로만 입력받고 로드해줘도 될듯 
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqHelmetData;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqChestData;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqPantsData;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqBootsData;


//////////////////////////////////////////////////////////////////////////////
// ** 기본 이벤트 함수 **
protected:
	virtual void Init() override;


//////////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	// Item Iventory에 추가 하는 함수
	void AddItem(FItemData* Data);
	

private:
	// *Data Table 관련 함수*
	void LoadDataTable(class UDataTable* DataTable);
	
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 내부 변수 **
private:
	// *Invenotry List* (Data Table에서 로드)
	TArray<FItemData*> HelmetsList;
	TArray<FItemData*> ChestsList;
	TArray<FItemData*> PantsList;
	TArray<FItemData*> BootsList;
	// 전체
	TArray<FItemData*> AllItemsList;

	
	
};
