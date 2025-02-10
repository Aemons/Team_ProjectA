// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_Gameover.generated.h"

/**
 * 
 */

class UHHR_ButtonBase;
class UWidgetAnimation;

UCLASS()
class TEAM_PROJECTA_API UHHR_Gameover : public UUserWidget
{
	GENERATED_BODY()


//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:
	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ButtonBase* RestartBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ButtonBase* GameendBtn;

	// *Animations*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Animations")
	UWidgetAnimation* Fade;	



//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수 **	
protected:
	virtual void NativeConstruct() override;


//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
private:
	// Button에 바인딩할 함수들
	UFUNCTION()
	void OnGameEnd();
	UFUNCTION()
	void OnRestart();
	
	
};
