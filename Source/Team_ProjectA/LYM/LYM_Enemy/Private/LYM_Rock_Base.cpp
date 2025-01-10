// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/LYM/LYM_Enemy/Public/LYM_Rock_Base.h"

void ALYM_Rock_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Sets default values
ALYM_Rock_Base::ALYM_Rock_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ALYM_Rock_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALYM_Rock_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
