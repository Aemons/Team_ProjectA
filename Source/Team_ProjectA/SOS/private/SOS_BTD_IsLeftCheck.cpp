// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BTD_IsLeftCheck.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "AIController.h"

USOS_BTD_IsLeftCheck::USOS_BTD_IsLeftCheck()
{
	NodeName = "Check bIsLeft == true";

	// Blackboard Key 필터를 Bool로 추가
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(USOS_BTD_IsLeftCheck, BlackboardKey));
}

bool USOS_BTD_IsLeftCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Blackboard 컴포넌트 확인
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}

	// 현재 조건 확인
	bool bIsLeft = BlackboardComp->GetValueAsBool(BlackboardKey.SelectedKeyName);

	//UE_LOG(LogTemp, Warning, TEXT("IsLeft: %s"), (bIsLeft ? TEXT("True") : TEXT("False")));

	return bIsLeft; // true면 Left, false면 Right
	
}
