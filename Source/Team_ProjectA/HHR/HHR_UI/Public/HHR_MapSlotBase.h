// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "HHR_MapSlotBase.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FOnMapSlotClicked, UHHR_MapSlotBase*);

class UButton;
class UBorder;
class UTextBlock;
class UImage;
class UWidgetAnimation;


// 변수화 필요한 요소 : 이미지, map 이름, map 차원 설명, 위험 등급, 점수(이건 나중에 동적으로 생성해줘야 할듯), + Map 이름 

UCLASS()
class TEAM_PROJECTA_API UHHR_MapSlotBase : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** ForceInline 함수 **
public:
	FORCEINLINE void SetIsCliked(bool IsClicked) { bIsClicked = IsClicked; }
	FORCEINLINE bool GetIsClicked() const { return bIsClicked; }
	FORCEINLINE void SetSelectBorderHidden() const { SelectBorder->SetVisibility(ESlateVisibility::Hidden); }

	

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
	
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	// Button의 텍스트 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText MapName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText LevelText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText PointText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText MapDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText LoadLevelName;
	
	
protected:  // *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UButton* HitBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UBorder* AnimBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UBorder* SelectBorder;
	// 세팅할 widget들 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UTextBlock* MapNameText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UImage* MapImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UTextBlock* MapLevelText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UTextBlock* MapPointText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UTextBlock* MapDescriptionText;

protected:	//*Animations*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category="Animations")
	UWidgetAnimation* Hover;
	
	
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
private:
	UFUNCTION()
	void OnHover();
	UFUNCTION()
	void OnUnHover();
	UFUNCTION()
	void OnClick();


//////////////////////////////////////////////////////////////////////////////
// ** 내부 변수 **

public: // *델리게이트 변수* 
	FOnMapSlotClicked OnMapSlotClicked;
	
private:
	bool bIsClicked = false;
	
};
