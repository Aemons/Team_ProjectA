#include "Team_ProjectA/SOS/public/SOS_BTD_DistanceCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

USOS_BTD_DistanceCheck::USOS_BTD_DistanceCheck()
{
	NodeName = "Distance Check";

	// Blackboard Key 필터를 Float로 추가
	TargetDistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTD_DistanceCheck, TargetDistanceKey));
}

bool USOS_BTD_DistanceCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Blackboard 컴포넌트 가져오기
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}

	// 거리 값 가져오기
	float TargetDistance = BlackboardComp->GetValueAsFloat(TargetDistanceKey.SelectedKeyName);

	// 거리 비교 조건
	bool bConditionMet = bLessThanOrEqual ? (TargetDistance <= DistanceThreshold) : (TargetDistance > DistanceThreshold);

	// 디버그 로그
	//UE_LOG(LogTemp, Warning, TEXT("Distance: %f, Threshold: %f, Result: %s"),
	//	TargetDistance, DistanceThreshold, bConditionMet ? TEXT("True") : TEXT("False"));

	// 조건 반환
	return bConditionMet;
}
