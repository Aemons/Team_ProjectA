// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "SOS_BTD_IsTargetOnRight.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTD_IsTargetOnRight : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	USOS_BTD_IsTargetOnRight();

protected:
	// 데코레이터 평가 함수
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	/** AI의 위치를 저장할 Blackboard Key */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector AIActorLocationKey;

	/** 목표 위치를 저장할 Blackboard Key */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetLocationKey;
	
};
