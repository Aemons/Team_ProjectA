// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_UIManager.h"

#include "Blueprint/UserWidget.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_Gameover.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_MapClear.h"

TObjectPtr<UHHR_UIManager> UHHR_UIManager::Instance = nullptr;

UHHR_UIManager::UHHR_UIManager()
{
	// Gameover 할당
	// TODO : 왜 이렇게 해야하는지 모르겠음 
	static ConstructorHelpers::FClassFinder<UUserWidget> gameoverWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/00_Project/HHR/HHR_UI/WBP/WBP_HHR_Gameover.WBP_HHR_Gameover_C'"));
	if(gameoverWidget.Succeeded())
	{
		GameoverUIWidget = gameoverWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> mapclearWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/00_Project/HHR/HHR_UI/WBP/WBP_HHR_MapClear_Test.WBP_HHR_MapClear_Test_C'"));
	if(mapclearWidget.Succeeded())
	{
		MapClearUIWidget = mapclearWidget.Class;
	}
	
}


UHHR_UIManager* UHHR_UIManager::GetUIManager()
{
	if(!Instance)
	{
		Instance = NewObject<UHHR_UIManager>();
		// GC에 의해 삭제되지 않도록 보호
		Instance->AddToRoot();
	}

	return Instance;
}

void UHHR_UIManager::CreateGameover()
{
	if(WorldContext && GameoverUIWidget)
	{
		// Gameover UI 생성
		UHHR_Gameover* Gameover = CreateWidget<UHHR_Gameover>(WorldContext, GameoverUIWidget);
		Gameover->AddToViewport();

		// UI mode로 세팅
		SetUIOnlyMode();
	}
	
}

void UHHR_UIManager::CreateMapClear()
{
	if(WorldContext && MapClearUIWidget)
	{
		UHHR_MapClear* MapClear = CreateWidget<UHHR_MapClear>(WorldContext, MapClearUIWidget);
		MapClear->AddToViewport();

		//SetUIOnlyMode();
	}
}

void UHHR_UIManager::Init()
{
	// WorldContext setting
	// TODO: 일단 안됨...
	WorldContext = GEngine->GetWorldFromContextObject(GetTransientPackage(), EGetWorldErrorMode::LogAndReturnNull);
	if(WorldContext)
	{
		PlayerController = WorldContext->GetFirstPlayerController();
	}
}

void UHHR_UIManager::Init(UWorld* World)
{
	// 임시
	WorldContext = World;
	if(World)
	{
		PlayerController = World->GetFirstPlayerController();
	}
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

void UHHR_UIManager::SetGameOnlyMode()
{
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetIgnoreLookInput(false);
	PlayerController->SetIgnoreMoveInput(false);

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
}

void UHHR_UIManager::SetUIOnlyMode()
{
	
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetIgnoreLookInput(true);
	PlayerController->SetIgnoreMoveInput(true);

	FInputModeUIOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	
}
 