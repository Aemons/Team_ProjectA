// Fill out your copyright notice in the Description page of Pr
// oject Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HHR_UIManager.generated.h"

/** UIManager
 * 싱글톤 
 * UI 생성 및 관리
 * Actor와 UI 간의 중재
 * UI 상태 관리
 */


UCLASS()
class TEAM_PROJECTA_API UHHR_UIManager : public UObject
{
	GENERATED_BODY()

// inline 함수
// UPROPERTY
// 기본 함수
// UFUNCTION
// 일반
// 클래스 내부에서 사용하는 일반 멤버 변수


// ** UPROPERTY 변수 **
//////////////////////////////////////////////////////////////////////////////
private:
	UPROPERTY(EditAnywhere, Category = "WidgetBlueprint")
	TSubclassOf<class UUserWidget> PlayerHUDWidget;

// ** 기본 생성 함수 **
//////////////////////////////////////////////////////////////////////////////
public:
	UHHR_UIManager();

// ** 일반 함수 **
//////////////////////////////////////////////////////////////////////////////
public:
	// 어디서든 접근 가능
	static UHHR_UIManager* GetUIManager();

	void Init(UWorld* World);

	// UI 생성 widget
	void CreateUI(TSubclassOf<UUserWidget> WidgetClass);

	// TODO : 임시 PlayerHUD 생성
	void CreatePlayerHUD();


// ** 내부에서만 사용하는 멤버 변수 **
//////////////////////////////////////////////////////////////////////////////
private:
	// 인스턴스
	static UHHR_UIManager* Instance;

	// World
	UPROPERTY()
	TObjectPtr<UWorld> WorldContext = nullptr;

	//UPROPERTY(EditDefaultsOnly, Category = "UI Widget")
	//TSubclassOf<class UHHR_StartMenu> StartMenuClass; 


//////////////////////////////////////////////////////////////////////////////
	
};
