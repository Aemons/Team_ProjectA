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


UENUM(BlueprintType)
enum class EPageType : uint8
{
	AllPage,
	HelmetPage,
	ChestPage,
	PantsPage,
	BootsPage,
	HandsPage,
};



UCLASS()
class TEAM_PROJECTA_API UHHR_InventoryPageBase : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	EPageType PageType;

	// ??? 외부에서 List를 추가하면 문제 발생 
	
protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UUniformGridPanel* GridPanel;


	

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

/////////////////////////////////////////////////////////////////////////
// ** 기본 함수 **
private:
	// GameInstance로부터 List 가져오기
	void GetInventoryData();
	// 가져온 list로부터 Data load
	void LoadItemData();
	

//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
private:
	int32 RowNum = 4;
	int32 ColumNum = 5;

	// GameInstance로부터 받아오는 Data list
	TArray<FItemData*> InventoryData;
	// 전체 ItemSlot
	TArray<UHHR_ItemSlotTest*> ItemSlotList;
	

};
