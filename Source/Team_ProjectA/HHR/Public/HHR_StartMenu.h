// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_StartMenu.generated.h"

// 델리게이트 선언

/**
 * 
 */

//
class UVerticalBox;
class UBorder;
class UVerticalBox;
class USpacer;
class UTextBlock;
class UHHR_ButtonBase;


UCLASS()
class TEAM_PROJECTA_API UHHR_StartMenu : public UUserWidget
{
	GENERATED_BODY()

	// inline 함수

	// UPROPERTY 변수(public, protected, private 순으로)
	
//*Componentns
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UBorder* Background;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UBorder* MenuBorder;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UVerticalBox* Menu;
	// menu 구성 요소
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	USpacer* Spacer1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UTextBlock* GameTitle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	USpacer* Spacer2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UHHR_ButtonBase* BtnComp_GameStart;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UHHR_ButtonBase* BtnComp_Setting;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets", meta = (BindWidget))
	UHHR_ButtonBase* BtnComp_GameEnd;

	// 기본 생성 함수

	// UFUNCTION 함수

	// 일반 함수

	// 클래스 내에서 사용하는 일반 멤버 변수 

	
};
