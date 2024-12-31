#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SOS_BTD_DistanceCheck.generated.h"

/**
 * 데코레이터: Target과 Self 간의 거리를 기준으로 조건을 판단
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTD_DistanceCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	USOS_BTD_DistanceCheck();

protected:
	// 조건을 계산하는 함수
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	// 디버깅 및 런타임 설정을 위해 필요한 Distance 변수
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetDistanceKey;

	// 거리 비교를 위한 기준값
	UPROPERTY(EditAnywhere, Category = "Condition")
	float DistanceThreshold = 500.0f; // 기본 거리 (500 유닛)

	// 비교 방식: 작거나 같으면 true, 크면 false
	UPROPERTY(EditAnywhere, Category = "Condition")
	bool bLessThanOrEqual = true; // 기본 설정: 작거나 같을 때 true 반환
};
