// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_MapClear.generated.h"

/**
 * 
 */


class UHHR_ButtonBase;

UCLASS()
class TEAM_PROJECTA_API UHHR_MapClear : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:
	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ButtonBase* ReChallengeBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ButtonBase* GoOutMapBtn;

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
	// * Button에 바인딩할 변수
	UFUNCTION()
	void OnReChallenge();
	UFUNCTION()
	void OnGoOUtMap();

	
};
