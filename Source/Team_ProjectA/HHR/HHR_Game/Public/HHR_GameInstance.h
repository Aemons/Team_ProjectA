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
UCLASS()
class TEAM_PROJECTA_API UHHR_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	// 내가 장착하고 있는 장비, 가지고 있는 장비 저장

	// !장착 데이터 로드, set
	// !가지고 있는 장비 추가 (삭제), get


//////////////////////////////////////////////////////////////////////////////
// ** FORCEINLINE 함수 **
public:
	FORCEINLINE FItemData* GetEqHelmetData() { return &EqHelmetData; }
	FORCEINLINE FItemData* GetEqChestData() { return &EqChestData; }
	FORCEINLINE FItemData* GetEqPantsData() { return &EqPantsData; }
	FORCEINLINE FItemData* GetEqBootsData() { return &EqBootsData; }

	FORCEINLINE void SetEqHelmetData(const FItemData* Data) { EqHelmetData = *Data; }
	FORCEINLINE void SetEqChestData(const FItemData* Data) { EqChestData = *Data; }
	FORCEINLINE void SetEqPantsData(const FItemData* Data) { EqPantsData = *Data; }
	FORCEINLINE void SetEqBootsData(const FItemData* Data) { EqBootsData = *Data; }
	

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqHelmetData;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqChestData;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqPantsData;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	FItemData EqBootsData;
	



	
	
};
