// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_MonsterHP.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_RetVal(float, FOnHPGetPercent);

class FText;
class UTextBlock;
class UProgressBar;

UCLASS()
class TEAM_PROJECTA_API UHHR_MonsterHP : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:     // *동적 변수* (상위 위젯에서 할당해줘야 하는 값들)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText MonsterName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FOnHPGetPercent OnHPGetPercent;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UTextBlock* MonsterTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category="Widgets")
	UProgressBar* HPProgressBar;

	
//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수
public:
	UFUNCTION(BlueprintCallable)
	float GetHPProgressBar() const;



//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
//////////////////////////////////////////////////////////////////////////////
// ** 기본 멤버 변수

	
};
