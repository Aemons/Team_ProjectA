// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_StoreNPC.h"


// Sets default values
AHHR_StoreNPC::AHHR_StoreNPC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHHR_StoreNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHHR_StoreNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHHR_StoreNPC::Interact()
{
	// TODO : 상점 UI 띄우기 + 관련 로직 처리
	if(!bIsWidgetOn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StoreNPC Interact"));
	}
	
}

