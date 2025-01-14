// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HHR_PlayerHUD.generated.h"

/**
 * 
 */
class UBorder;
class UProgressBar;
class UImage;
class UHorizontalBox;
class UHHR_ItemSlotBase;
class UHHR_Interact;
class UOverlay;

UCLASS()
class TEAM_PROJECTA_API UHHR_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

// PlayerHUD는 PlayerController에서 생성 (PlayerController가 생성될때 생성해주면 될듯) 
// TODO : 아이템 슬롯 연결

/////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:	// *Widgets*
	// Statmina
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* BorderStat;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UProgressBar* StatminaBar;
	// Health 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UBorder* BorderHP;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UOverlay* HealthOverlay;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UProgressBar* DelayHPBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UProgressBar* HPBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UImage* StatueIMG;
	// item slot comp widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHorizontalBox* ItemSlot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ItemSlotBase* ItemSlotComp_Slot1;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_ItemSlotBase* ItemSlotComp_Slot2;
	// Interact widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Widgets")
	UHHR_Interact* InteractUIComp;
	
private:	// *Timeline Curve*
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess), Category = "Timeline")
	class UCurveFloat* HealthCurveFloat;

	

/////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry & MyGeometry, float DeltaTime) override;

/////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
public:
	// 델리게이트에 바인딩할 함수 (데미지를 받을 경우 호출)
	// TODO : 아이템을 먹고 hp가 올라가는 것도 구현 필요 
	UFUNCTION(BlueprintCallable)
	void DecreaseHPBar(float CurrentHealth);
	
protected:
	// Statmina 적용 함수 (PlayerCharacter의 Statmina 변수와 바인딩)
	UFUNCTION(BlueprintCallable)
	float GetStatminPercent() const;

private:	// *Timeline 바인딩 함수*
	UFUNCTION()
	void OnTimelineUpdate(float Value);
	UFUNCTION()
	void OnTimelineFinish();

/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
	
/////////////////////////////////////////////////////////////////////////
// ** 클래스 내에서만 사용하는 멤버 변수 **
private:
	// Health 변수
	float CachedHelath = 100;
	float DelayCachedHelath = 100;
	
	// Timeline 변수
	struct FTimeline* DelayHealthTimeline;
	
	
};
