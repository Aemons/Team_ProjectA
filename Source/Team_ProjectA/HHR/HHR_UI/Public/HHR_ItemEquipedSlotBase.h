// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_ItemEquipedSlotBase.generated.h"

/**
 * 
 */

class UButton;
class UBorder;
class UTexture2D;
class UWidgetAnimation;

// *Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEqBtnClickMessage, int32, ItemMenuIdx);


UCLASS()
class TEAM_PROJECTA_API UHHR_ItemEquipedSlotBase : public UUserWidget
{
	GENERATED_BODY()

// ** FORCEINLINE 함수 **
public:
	/*FORCEINLINE void SetIsSelected(bool b){bIsSelected = b;};
	FORCEINLINE bool GetIsSelected() const {return bIsSelected;};*/
	

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	// Button의 텍스트 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	int32 ItemMenuIdx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	bool bIsSelected = false;
	
protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UButton* ItemButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UBorder* SelectedBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UBorder* ItemIcon;

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
	// *비주얼 업뎃*
	void Selected();
	void Unselected();
	

//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **

public: //*Delegate*
	FOnEqBtnClickMessage OnBtnClickMessage;

	
/*private:
	bool bIsSelected = false;*/
	
};
