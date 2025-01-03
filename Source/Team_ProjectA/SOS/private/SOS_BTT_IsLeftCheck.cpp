// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BTT_IsLeftCheck.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


USOS_BTT_IsLeftCheck::USOS_BTT_IsLeftCheck()
{
	NodeName = "Calculate Target Side";

	AIActorLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTT_IsLeftCheck, AIActorLocationKey));
	TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTT_IsLeftCheck, TargetLocationKey));
	ResultKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTT_IsLeftCheck, ResultKey));
}

EBTNodeResult::Type USOS_BTT_IsLeftCheck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Blackboard 값 가져오기
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	FVector AIActorLocation = BlackboardComp->GetValueAsVector(AIActorLocationKey.SelectedKeyName);
	FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}

	FVector ForwardVector = AIController->GetPawn()->GetActorForwardVector();
	FVector DirectionToTarget = (TargetLocation - AIActorLocation).GetSafeNormal();
	float CrossZ = FVector::CrossProduct(ForwardVector, DirectionToTarget).Z;

	bool bIsOnLeft = CrossZ > 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("Task - CrossZ: %f, IsLeft: %s"), CrossZ, (bIsOnLeft ? TEXT("True") : TEXT("False")));

	// 결과를 Blackboard에 저장
	BlackboardComp->SetValueAsBool(ResultKey.SelectedKeyName, bIsOnLeft);

	return EBTNodeResult::Succeeded;
}

