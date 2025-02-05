// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_HeaderMenu.generated.h"

/**
 * 
 */

class UHHR_HeaderButton;


UCLASS()
class TEAM_PROJECTA_API UHHR_HeaderMenu : public UUserWidget
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
	UHHR_HeaderButton* AllBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_HeaderButton* HelmetBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_HeaderButton* ChestBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_HeaderButton* PantsBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_HeaderButton* HandsBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UHHR_HeaderButton* BootsBtn;
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativeConstruct() override;

	
//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
public:
	// Button의 click 델리게이트에 연결할 함수 -> click 관리
	UFUNCTION()
	void OnMenuUpdate(int MenuIdx);


//////////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:

	
	
private:	//*내부에서만 사용하는 함수들*
	int32 FindClickedIndex();
	

//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
public:
	// 외부에서 사용할 버튼 리스트
	TArray<UHHR_HeaderButton*> MenuBtnList;
	
	
};
