// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_UIManager.h"

#include "Blueprint/UserWidget.h"

UHHR_UIManager* UHHR_UIManager::Instance = nullptr;

UHHR_UIManager::UHHR_UIManager()
{
	// PlayerHUD 할당
	static ConstructorHelpers::FObjectFinder<UUserWidget> widgetBPAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/00_Project/HHR/HHR_UI/WBP/WBP_HHR_PlayerHUD.WBP_HHR_PlayerHUD'"));
	if(widgetBPAsset.Succeeded())
	{
		PlayerHUDWidget = widgetBPAsset.Object->StaticClass();
	}
	
}

UHHR_UIManager* UHHR_UIManager::GetUIManager()
{
	if(!Instance)
	{
		Instance = NewObject<UHHR_UIManager>();
	}

	return Instance;
}

void UHHR_UIManager::Init(UWorld* World)
{
	WorldContext = World;

	// 임시 
}

void UHHR_UIManager::CreateUI(TSubclassOf<UUserWidget> WidgetClass)
{
	UUserWidget* Widget = CreateWidget<UUserWidget>(WorldContext, WidgetClass);
	if(Widget)
	{
		Widget->AddToViewport();
	}
}

void UHHR_UIManager::CreatePlayerHUD()
{
	if(PlayerHUDWidget)
	{
		UUserWidget* playerHUD = CreateWidget<UUserWidget>(WorldContext, PlayerHUDWidget);
		if(playerHUD)
		{
			playerHUD->AddToViewport();
		}
	}
}
 