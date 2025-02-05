// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_SquareButtonBase.generated.h"

class UTextBlock;


/**
 * 
 */


UCLASS()
class TEAM_PROJECTA_API UHHR_SquareButtonBase : public UUserWidget
{
	GENERATED_BODY()

	
//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	// Button의 텍스트 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	float TextSize;
protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UTextBlock* BtnText;

//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;
	
};
