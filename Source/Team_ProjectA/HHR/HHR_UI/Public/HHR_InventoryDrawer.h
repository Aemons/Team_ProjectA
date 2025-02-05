// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_InventoryDrawer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPageSwitch, int32, MenuIdx);

/**
 * 
 */

class UHHR_HeaderMenu;
class UHHR_InventoryPageBase;
class UWidgetSwitcher;


UCLASS()
class TEAM_PROJECTA_API UHHR_InventoryDrawer : public UUserWidget
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
	UHHR_HeaderMenu* HeaderMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UWidgetSwitcher* PageSwitcher;

	
	
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativeConstruct() override;


//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
private:	// *델리게이트 바인딩 함수*
	UFUNCTION()
	void OnSwitchPage(int32 PageIdx);

//////////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	void UpdateDrawer(int32 PageIdx);

	
//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
public:
	FOnPageSwitch OnPageSwitch;

	
	
};
