// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_InteractDialog.generated.h"

/**
 * 
 */

class UHorizontalBox;
class UBorder;
class UTextBlock;
class USpacer;

UCLASS()
class TEAM_PROJECTA_API UHHR_InteractDialog : public UUserWidget
{
	GENERATED_BODY()

// ** UPROPERTY **
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHorizontalBox* HorizontalBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* KeyBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* KeyBackground;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UTextBlock* KeyText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	USpacer* Spacer;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* InteractBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UTextBlock* InteractText;




	
};
