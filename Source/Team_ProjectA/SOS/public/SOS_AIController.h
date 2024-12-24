// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SOS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API ASOS_AIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit ASOS_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
