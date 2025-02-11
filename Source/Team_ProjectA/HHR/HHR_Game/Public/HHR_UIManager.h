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



// ** UPROPERTY 변수 **
//////////////////////////////////////////////////////////////////////////////
private:
	UPROPERTY(EditAnywhere, Category = "WidgetBlueprint")
	TSubclassOf<class UUserWidget> PlayerHUDWidget;

	UPROPERTY(EditAnywhere, Category = "WidgetBlueprint")
	TSubclassOf<class UUserWidget> GameoverUIWidget;

// ** 기본 생성 함수 **
//////////////////////////////////////////////////////////////////////////////
private:
	// 생성자 비공개 처리
	UHHR_UIManager();

// ** UFUNCTION 함수 **
//////////////////////////////////////////////////////////////////////////////
public:
	// 어디서든 접근 가능
	UFUNCTION(BlueprintCallable) 
	static UHHR_UIManager* GetUIManager();

	// Gameover UI 생성
	UFUNCTION(BlueprintCallable)
	void CreateGameover();

// ** 일반 함수 **
//////////////////////////////////////////////////////////////////////////////
public:

	void Init();
	void Init(UWorld* World);

	// UI 생성 widget
	void CreateUI(TSubclassOf<UUserWidget> WidgetClass);

	// TODO : 임시 PlayerHUD 생성
	void CreatePlayerHUD();


public:
	// Game ui mode로 세팅
	void SetGameOnlyMode();
	
private:
	// UIOnly mode로 세팅
	void SetUIOnlyMode();


// ** 내부에서만 사용하는 멤버 변수 **
//////////////////////////////////////////////////////////////////////////////
private:
	// 인스턴스
	static TObjectPtr<UHHR_UIManager> Instance;

	// World
	UPROPERTY()
	TObjectPtr<UWorld> WorldContext = nullptr;

	// Controller
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController = nullptr;

	//UPROPERTY(EditDefaultsOnly, Category = "UI Widget")
	//TSubclassOf<class UHHR_StartMenu> StartMenuClass; 


//////////////////////////////////////////////////////////////////////////////
	
};
