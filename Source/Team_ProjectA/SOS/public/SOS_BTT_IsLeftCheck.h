// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SOS_BTT_IsLeftCheck.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTT_IsLeftCheck : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


	
public:
	USOS_BTT_IsLeftCheck();
	
protected:
	// Execute Task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector AIActorLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ResultKey; // 결과 저장용
	
};
