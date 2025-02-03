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

	// 주기적으로 거리를 계산
	virtual void Tick(float DeltaTime) override;

private:
	// Blackboard에 저장할 거리의 키 이름
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	FName DistanceKey = TEXT("SOS_TargetDistance");

	
	
};
