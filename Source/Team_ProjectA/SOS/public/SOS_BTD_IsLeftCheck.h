// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "SOS_BTD_IsLeftCheck.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTD_IsLeftCheck : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	USOS_BTD_IsLeftCheck();

protected:
	/** 데코레이터의 조건을 계산 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
