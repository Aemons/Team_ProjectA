// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_MapSelect.generated.h"

/**
 * 
 */

class UCanvasPanel;
class UBorder;
class UHorizontalBox;
class UVerticalBox;
class UTextBlock;
class UHHR_MapSlotBase;
class USpacer;
class UHHR_ButtonBase;


UCLASS()
class TEAM_PROJECTA_API UHHR_MapSelect : public UUserWidget
{
	GENERATED_BODY()

/////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
	
protected:	//*Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ButtonBase* BtnComp_MapSelect;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ButtonBase* BtnComp_Close;

	// TODO : 나중에 데이터 테이블로 관리하면 수정
	// MapSelect slot
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_MapSlotBase* MapComp_Map1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_MapSlotBase* MapComp_Map2;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_MapSlotBase* MapComp_Map1_Test1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_MapSlotBase* MapComp_Map1_Test2;

/////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수 **
protected:
	virtual void NativeConstruct() override;

/////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
private:
	UFUNCTION()
	void OnClickCloseBtn();
	UFUNCTION()
	void OnClickMapSelectBtn();

/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
private:
	// MapSlotBase가 click되면 호출
	void MapClick(UHHR_MapSlotBase* ClickedMap);

private:
	UHHR_MapSlotBase* CheckClickedSlot();

/////////////////////////////////////////////////////////////////////////
// ** 내부에서 사용하는 변수 **
private:
	// 현재 선택된 Map
	TObjectPtr<UHHR_MapSlotBase> SelectedMap = nullptr;
	
	// MapComp 변수
	TArray<UHHR_MapSlotBase*> MapSlots;
	
};
