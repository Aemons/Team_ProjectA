// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BTT_LookAtPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USOS_BTT_LookAtPlayer::USOS_BTT_LookAtPlayer()
{
	bNotifyTick = true; // TickTask 활성화
	NodeName = "Look At Player While Playing Montage";
	bIsPlayingMontage = false; // 초기화
}

EBTNodeResult::Type USOS_BTT_LookAtPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// AIController와 Controlled Pawn 가져오기
	AAIController* AIController = OwnerComp.GetAIOwner();
	
	ACharacter* ControlledCharacter = AIController ? AIController->GetCharacter() : nullptr;

	// ControlledPawn이 ACharacter인지 확인
	//ACharacter* Character = Cast<ACharacter>(ControlledPawn);

	if (ControlledCharacter && MontageToPlay)
	{
		// 몽타주가 이미 재생 중인지 확인
		if (!ControlledCharacter->GetMesh()->GetAnimInstance()->Montage_IsPlaying(MontageToPlay))
		{
			ControlledCharacter->PlayAnimMontage(MontageToPlay);
			bIsPlayingMontage = true;
		}
	}
	else
	{
		// 캐스팅 실패 또는 MontageToPlay가 nullptr인 경우 처리
		return EBTNodeResult::Failed;
	}

	// 플레이어 액터 가져오기
	PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerActor)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress; // 작업이 진행 중임을 반환
}


void USOS_BTT_LookAtPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// AIController와 Controlled Pawn 가져오기
	AAIController* AIController = OwnerComp.GetAIOwner();
	ACharacter* ControlledCharacter = AIController ? AIController->GetCharacter() : nullptr;

	// ControlledPawn이 ACharacter인지 확인
	//ACharacter* Character = Cast<ACharacter>(ControlledPawn);
	if (!ControlledCharacter || !PlayerActor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 현재 회전과 목표 회전 계산
	FRotator CurrentRotation = ControlledCharacter->GetActorRotation();
	FVector DirectionToPlayer = PlayerActor->GetActorLocation() - ControlledCharacter->GetActorLocation();
	DirectionToPlayer.Z = 0; // Z축 무시하여 수평 회전만 고려
	FRotator TargetRotation = DirectionToPlayer.Rotation();

	// 목표 회전으로 일정 속도로 회전
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);
	ControlledCharacter->SetActorRotation(NewRotation);

	// 몽타주 재생 상태 확인
	if (bIsPlayingMontage && !ControlledCharacter->GetMesh()->GetAnimInstance()->Montage_IsPlaying(MontageToPlay))
	{
		bIsPlayingMontage = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


void USOS_BTT_LookAtPlayer::FinishTask(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type Result)
{
	FinishLatentTask(OwnerComp, Result);
}
