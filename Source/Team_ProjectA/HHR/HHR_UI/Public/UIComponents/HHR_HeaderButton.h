// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_HeaderButton.generated.h"

/**
 * 
 */

class UTexture2D;
class UBorder;

UCLASS()
class TEAM_PROJECTA_API UHHR_HeaderButton : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	// Header 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	UTexture2D* IconImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FSlateColor IconColor;

protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Widgets")
	UBorder* IconBorder;

//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;



	
	
};
