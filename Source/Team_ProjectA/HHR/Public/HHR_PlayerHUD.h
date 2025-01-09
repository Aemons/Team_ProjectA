// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_PlayerHUD.generated.h"

/**
 * 
 */
class UBorder;
class UProgressBar;
class UImage;
class UHorizontalBox;
class UHHR_ItemSlotBase;

UCLASS()
class TEAM_PROJECTA_API UHHR_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

// ** UPROPERTY 변수 **
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* BorderStat;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UProgressBar* StatminaBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* BorderHP;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UProgressBar* HPBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UImage* Statue;
	// item slot comp widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ItemSlotBase* ItemSlotComp_Slot1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ItemSlotBase* ItemSlotComp_Slot2;

// PlayerHUD는 PlayerController에서 생성 (PlayerController가 생성될때 생성해주면 될듯) 
// TODO : HP, Statmina 연결, 아이템 슬롯 연결
// - +추가) HP 다는 anim 적용

	
};
