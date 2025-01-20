// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_MapNPC.h"

// Test
#include "Blueprint/UserWidget.h"


// Sets default values
AHHR_MapNPC::AHHR_MapNPC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHHR_MapNPC::BeginPlay()
{
	Super::BeginPlay();	
	
}

// Called every frame
void AHHR_MapNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHHR_MapNPC::Interact()
{
	
	// Create Map Widget
	// TODO : UIManger에서 처리해줘야 함 
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), MapSelectWidgetClass);
	if(widget)
	{
		widget->AddToViewport();
	}
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	
}

