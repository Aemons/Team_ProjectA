// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_ButtonBase.generated.h"


class UOverlay;
class UImage;
class UBorder;
class UTextBlock;
class UButton;
class UWidgetAnimation;

UCLASS()
class TEAM_PROJECTA_API UHHR_ButtonBase : public UUserWidget
{
	GENERATED_BODY()

// ** UPROPERTY 변수 **
//*다른 widget에서 편집할 수 있는 변수*
public:
	// Button의 텍스트 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	float TextSize;
	// Button의 텍스트 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText Text;
//*Widget Component*
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UOverlay* Overlay;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UImage* Background;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UBorder* TextBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UTextBlock* BtnText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UButton* HitBox;
	// Animation
	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetAnim), Transient, Category="Animations")
	UWidgetAnimation* Hover;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category="Animations")
	UWidgetAnimation* Click;




// **기본 생성 함수**
protected:
	// 위젯 바인딩이 완료된 상태 
	// Blueprint와 연동 작업 전에 실행, 디자인 스타일 관련 초기화 작업 수행 
	virtual void NativePreConstruct() override;
	// 위젯 완성된 후에 호출 (위젯이 화면에 표시되기 전에 실행)
	// 위젯 component에 이벤트 바인딩
	// Viewport에 add 될때 호출..?
	virtual void NativeConstruct() override;


// **UFUNCTION 함수**
//*Button 이벤트에 바인딩 될 함수들*
private:
	UFUNCTION()
	void OnClicked();
	UFUNCTION()
	void OnHovered();
	UFUNCTION()
	void OnUnhoverd();
	
	
};
