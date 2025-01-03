// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BTD_IsTargetOnLeft.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

USOS_BTD_IsTargetOnLeft::USOS_BTD_IsTargetOnLeft()
{
	// Blackboard 키 기본값 설정
	NodeName = "Is Target On Left";

	// Blackboard Key 초기화
	//AIActorLocationKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTD_IsTargetOnLeft, AIActorLocationKey), AActor::StaticClass());
	AIActorLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTD_IsTargetOnLeft, AIActorLocationKey));
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTD_IsTargetOnLeft, TargetLocationKey));
	ResultKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTD_IsTargetOnLeft, ResultKey)); // 결과 저장용
}

bool USOS_BTD_IsTargetOnLeft::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Blackboard 값 가져오기
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}

	// AI 위치와 목표 위치 가져오기
	FVector AIActorLocation = BlackboardComp->GetValueAsVector(AIActorLocationKey.SelectedKeyName);
	FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

	// AI Pawn 가져오기
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return false;
	}

	FVector ForwardVector = AIController->GetPawn()->GetActorForwardVector();
	FVector DirectionToTarget = (TargetLocation - AIActorLocation).GetSafeNormal();
	float CrossZ = FVector::CrossProduct(ForwardVector, DirectionToTarget).Z;

	// CrossProduct 결과로 왼쪽/오른쪽 판별
	bool bIsOnLeft = CrossZ > 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("CrossZ: %f, IsLeft: %s"), CrossZ, (CrossZ > 0.0f ? TEXT("True") : TEXT("False")));

	// 결과를 Blackboard에 저장
	BlackboardComp->SetValueAsBool(ResultKey.SelectedKeyName, bIsOnLeft);

	// Z 축이 양수이면 왼쪽, 음수이면 오른쪽
	return CrossZ > 0.0f; // 왼쪽이면 true 반환
	
}