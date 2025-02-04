// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
#include "HHR_Test.generated.h"

/**
 * 
 */

class UButton;
class UBorder;


UCLASS()
class TEAM_PROJECTA_API UHHR_Test : public UUserWidget
{
	GENERATED_BODY()

	//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY ���� **
public:     // *���� ����* (���� �������� �Ҵ������ �ϴ� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editable")
	FItemData ItemData;

protected:	// *Widgets*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category = "Widgets")
	UButton* ItemButton;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category = "Widgets")
	UBorder* SelectedBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Transient, Category = "Widgets")
	UBorder* ItemImage;

protected:	// *Animations*
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient, Category = "Animations")
	UWidgetAnimation* HoverEffect;

	//////////////////////////////////////////////////////////////////////////////
	// ** �⺻ ���� �Լ�
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	//////////////////////////////////////////////////////////////////////////////
	// **UFUNCTION �Լ�**
private:	//*Button �̺�Ʈ�� ���ε� �� �Լ���*
	UFUNCTION()
	void OnHovered();
	UFUNCTION()
	void OnUnHovered();
	UFUNCTION()
	void OnClicked();

	//////////////////////////////////////////////////////////////////////////////
	// **�Ϲ� �Լ�**
public:
	void UpdateItemData(FItemData* Data);

	
};
