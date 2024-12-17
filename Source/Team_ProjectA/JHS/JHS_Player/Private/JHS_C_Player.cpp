// Fill out your copyright notice in the Description page of Project Settings.


//#include "Team_ProjectA/JHS/JHS_Player/Public/JHS_C_Player.h"
#include "JHS_C_Player.h"

// Sets default values
AJHS_C_Player::AJHS_C_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJHS_C_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJHS_C_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJHS_C_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

