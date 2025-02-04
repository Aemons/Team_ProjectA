// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_Inventory.generated.h"

/**
 * 
 */


struct FItemData;
class UHHR_ItemEquipedSlotBase;
class UHHR_InventoryDrawer;

UCLASS()
class TEAM_PROJECTA_API UHHR_Inventory : public UUserWidget
{
	GENERATED_BODY()

// ** FORCEINLINE 함수 **
public:
	//FORCEINLINE TArray<UHHR_HeaderButton*> GetHeaderButtonList() {return MenuBtnList; }

	//////////////////////////////////////////////////////////////////////////////
	// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	// Header 이름
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")


protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_InventoryDrawer* InventoryDrawer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_ItemEquipedSlotBase* HelmetSlot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_ItemEquipedSlotBase* ChestSlot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_ItemEquipedSlotBase* HandsSlot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_ItemEquipedSlotBase* PantsSlot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_ItemEquipedSlotBase* BootsSlot;

	
	
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativeConstruct() override;


//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
// *델리게이트 바인딩 함수*
public:
	UFUNCTION()
	void UpdateItemEqSlot(int32 ItemMenuIdx);
private:
	// ItemSlot에서 호출할 함수
	UFUNCTION()
	void OnUpdateEquipedSlot(int32 ItemMenuIdx);

//////////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	void ChangeHelemtSlot(FItemData* Data);
	void ChangeChestSlot(FItemData* Data);
	void ChangePantsSlot(FItemData* Data);
	void ChangeBootsSlot(FItemData* Data);


//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **

private:
	// Btn 쉽게 관리하기 위한
	TArray<UHHR_ItemEquipedSlotBase*> ItemSlotList;

	int32 SelectedSlotIdx = 0;
	
};
