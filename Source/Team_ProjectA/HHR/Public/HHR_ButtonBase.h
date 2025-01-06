// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_ButtonBase.generated.h"

/**
 * 
 */

class UOverlay;
class UImage;
class UBorder;
class UTextBlock;
class UButton;

UCLASS()
class TEAM_PROJECTA_API UHHR_ButtonBase : public UUserWidget
{
	GENERATED_BODY()


//*Widget Component
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widgets", meta = (BindWidget))
	UOverlay* Overlay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widgets", meta = (BindWidget))
	UImage* Background;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widgets", meta = (BindWidget))
	UBorder* TextBorder;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widgets", meta = (BindWidget))
	UTextBlock* BtnText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Widgets", meta = (BindWidget))
	UButton* HitBox;
	
};
