// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
#include "HHR_InventoryPageBase.generated.h"

/**
 * 
 */

class UUniformGridPanel;
class UHHR_ItemSlotBase;
class UHHR_ItemSlotTest;

UCLASS()
class TEAM_PROJECTA_API UHHR_InventoryPageBase : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	TArray<UHHR_ItemSlotTest*> HaveItemSlotList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	TArray<FItemData> ItemDataList;
	
protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UUniformGridPanel* GridPanel;

	// 임시 노가다
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot3;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot4;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot5;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot6;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot7;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot8;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot9;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot10;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot11;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UHHR_ItemSlotTest* ItemSlot12;
	

private:
	// 동적으로 itemslot을 생성해주기 위한 Class
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess), Category="ItemSlot Class")
	TSubclassOf<UHHR_ItemSlotTest> ItemSlotClass;


//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;


/////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
private:
	// Inventory
	UFUNCTION()
	void UpdateSlotClick(UHHR_ItemSlotTest* ClickItem);


//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
private:
	int32 RowNum = 4;
	int32 ColumNum = 5;

	// 전체 ItemSlot
	TArray<UHHR_ItemSlotTest*> ItemSlotList;
	

};
