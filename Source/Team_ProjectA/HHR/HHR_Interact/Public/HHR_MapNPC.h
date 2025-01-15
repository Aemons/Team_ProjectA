// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HHR_NPCBase.h"
#include "HHR_MapNPC.generated.h"

UCLASS()
class TEAM_PROJECTA_API AHHR_MapNPC : public AHHR_NPCBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHHR_MapNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	virtual void Interact() override;

	
};
