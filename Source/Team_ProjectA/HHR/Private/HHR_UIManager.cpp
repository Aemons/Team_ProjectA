// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/Public/HHR_UIManager.h"

#include "Blueprint/UserWidget.h"

UHHR_UIManager* UHHR_UIManager::Instance = nullptr;

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
}

void UHHR_UIManager::CreateUI(TSubclassOf<UUserWidget> WidgetClass)
{
	UUserWidget* Widget = CreateWidget<UUserWidget>(WorldContext, WidgetClass);
	if(Widget)
	{
		Widget->AddToViewport();
	}
}
 