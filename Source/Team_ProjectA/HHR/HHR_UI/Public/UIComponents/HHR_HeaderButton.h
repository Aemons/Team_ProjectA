// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_HeaderButton.generated.h"

/**
 * 
 */

// ** 델리게이트 **
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBtnClickMessage, int32, index);



class UTexture2D;
class UBorder;
class UButton;

UCLASS()
class TEAM_PROJECTA_API UHHR_HeaderButton : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** FORCEINLINE 함수 **
public:
	/*FORCEINLINE void SetIsSelected(bool b){ bIsSelected = b; }
	FORCEINLINE bool GetIsSelected() const { return bIsSelected; }*/

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	// Header 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	UTexture2D* IconImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FSlateColor IconColor;

	// Header button click 되어 있는지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	bool bIsSelected = false;

	
	// 일단 안사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	int32 MenuIndex;

protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UBorder* IconBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UButton* HitBox;

//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;


//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
public:		// *selected, unselected 함수 (bp에서 구현)
	UFUNCTION(BlueprintImplementableEvent)
	void OnSelected();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnSelected();
	
private:	// *델리게이트 바인딩 함수*
	UFUNCTION()
	void OnClicked();
	

//////////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
private:


//////////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
public:		// *델리게이트 변수*
	FOnBtnClickMessage OnClickMessage;
	

	
/*private:
	bool bIsSelected = false;*/
	
};
