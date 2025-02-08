// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
#include "HHR_ItemSlotTest.generated.h"

/**
 * 
 */

class UButton;
class UBorder;


// *Delegate
// TODO : ItemSlotTest를 전달해줘도 될듯
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemChanged, UHHR_ItemSlotTest*, ClickItem);


UCLASS()
class TEAM_PROJECTA_API UHHR_ItemSlotTest : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FItemData ItemData;

	// Default 값이 hidden
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	bool bIsSelected;
	
protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UButton* ItemButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UBorder* SelectedBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UBorder* ItemImage;

protected:	// *Animations*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category="Animations")
	UWidgetAnimation* HoverEffect;

//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;
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

//////////////////////////////////////////////////////////////////////////////
// **일반 함수**
public:
	// Data Set
	void SetData(FItemData* Data);
	// 가지고 있는 Data Rendering
	void RenderData();
	

	// visible 업뎃 함수
	void ChangeSelected();
	void ChangeUnSelected();

private:
	void LoadPlayerSelected();

//////////////////////////////////////////////////////////////////////////////
// **내부 멤버 변수 **

public:	//*Delegate*
	FOnItemChanged OnItemChanged;



	
	
};
