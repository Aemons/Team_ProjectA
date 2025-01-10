// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BTT_IncreaseSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"

USOS_BTT_IncreaseSpeed::USOS_BTT_IncreaseSpeed()
{
	NodeName = "Increase Speed and Change Blackboard Status";
}

EBTNodeResult::Type USOS_BTT_IncreaseSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// AI Controller 가져오기
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController is nullptr in %s"), *NodeName);
		return EBTNodeResult::Failed;
	}

	// 컨트롤 중인 캐릭터 가져오기
	ACharacter* ControlledCharacter = Cast<ACharacter>(AIController->GetPawn());
	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("ControlledCharacter is nullptr in %s"), *NodeName);
		return EBTNodeResult::Failed;
	}

	// 캐릭터의 이동 속도 증가
	UCharacterMovementComponent* MovementComponent = ControlledCharacter->GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->MaxWalkSpeed *= SpeedMultiplier; // 기존 속도에 1.5배
		// UE_LOG(LogTemp, Warning, TEXT("Speed increased to %f"), MovementComponent->MaxWalkSpeed);
	}
	else
	{
		// UE_LOG(LogTemp, Error, TEXT("MovementComponent is nullptr in %s"), *NodeName);
		return EBTNodeResult::Failed;
	}

	
	// 몽타주(스킬 재생속도 증가 (fail)
	// ASOS_BOSS_Character* Boss_Character = Cast<ASOS_BOSS_Character>(AIController->GetPawn());
	// Boss_Character->SetMontagePlayRate(5.0f);
	
	
	// Blackboard Key 변경
	if (AIController && AIController->GetBlackboardComponent())
	{
		// Set Blackboard Key Value
		AIController->GetBlackboardComponent()->SetValueAsEnum("SOS_State", 0);
		// UE_LOG(LogTemp, Warning, TEXT("Blackboard Key 'SOS_State' updated to Enum Value '0 Attack'."));

		
	}

	return EBTNodeResult::Succeeded;
}

