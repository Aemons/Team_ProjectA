// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/LYM/LYM_Enemy/Public/LYM_Enemy_Base.h"

// Sets default values
ALYM_Enemy_Base::ALYM_Enemy_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALYM_Enemy_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALYM_Enemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALYM_Enemy_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

