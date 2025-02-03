// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_ItemSlotBase.generated.h"

/**
 * 
 */


class UButton;
class UBorder;

UCLASS()
class TEAM_PROJECTA_API UHHR_ItemSlotBase : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UButton* ItemButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UBorder* SelectedBorder;


protected:	// *Animations*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category="Animations")
	UWidgetAnimation* HoverEffect;
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativeConstruct() override;

//////////////////////////////////////////////////////////////////////////////
// **UFUNCTION 함수**
private:	//*Button 이벤트에 바인딩 될 함수들*
	UFUNCTION()
	void OnHovered();
	UFUNCTION()
	void OnUnHovered();
	UFUNCTION()
	void OnClicked();
	
};
