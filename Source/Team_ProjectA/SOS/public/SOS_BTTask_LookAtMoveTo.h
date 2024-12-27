// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SOS_BTTask_LookAtMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTTask_LookAtMoveTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USOS_BTTask_LookAtMoveTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FVector TargetLocation;  // 이동 목표 위치
	bool bIsMoving;          // 이동 중인지 확인
	UPROPERTY(EditAnywhere)
	float DistanceTarget = 300.0;
	
};
