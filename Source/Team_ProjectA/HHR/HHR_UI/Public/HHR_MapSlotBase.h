// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_MapSlotBase.generated.h"

/**
 * 
 */

// 변수화 필요한 요소 : 이미지, map 이름, map 차원 설명, 위험 등급, 점수(이건 나중에 동적으로 생성해줘야 할듯)  

UCLASS()
class TEAM_PROJECTA_API UHHR_MapSlotBase : public UUserWidget
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
public:
	// Button의 텍스트 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	float TextSize;
	// Button의 텍스트 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Editable")
	FText Text;
//////////////////////////////////////////////////////////////////////////////

	
	
	
};
