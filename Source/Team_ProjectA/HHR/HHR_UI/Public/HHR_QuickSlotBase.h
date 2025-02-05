// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_QuickSlotBase.generated.h"

/**
 * 
 */

class UBorder;
class UOverlay;
class UImage;

UCLASS()
class TEAM_PROJECTA_API UHHR_QuickSlotBase : public UUserWidget
{
	GENERATED_BODY()

// ** UPROPERTY 변수 **
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* Border;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UOverlay* Overlay;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UImage* ItemIMG;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UImage* TimeCheck;


// TODO : Inventory 구현할때 구현
// - Inventory에서 퀵슬롯 설정
// - 설정 반영해서  UI로 띄위기 (해당 기능을 수행하는 함수만 따로 만들어두고 PlayerHUD에서 호출)
// - +추가) item 사용시 일정 기간 동안 사용 제한 기능 추가

	
};
