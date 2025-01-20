// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BTT_DistanceMove.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

USOS_BTT_DistanceMove::USOS_BTT_DistanceMove()
{
	bNotifyTick = true; // TickTask 활성화
	NodeName = "DistanceMove";
	bIsPlayingMontage = false; // 초기화
}

EBTNodeResult::Type USOS_BTT_DistanceMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void USOS_BTT_DistanceMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// AIController와 Controlled Pawn 가져오기
	AAIController* AIController = OwnerComp.GetAIOwner();
	ACharacter* ControlledCharacter = AIController ? AIController->GetCharacter() : nullptr;

	// ControlledPawn이 ACharacter인지 확인
	if (!ControlledCharacter || !PlayerActor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// BlackboardComponent 가져오기
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (!BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// BlackboardKey 값 확인
	float TargetDistance = BlackboardComp->GetValueAsFloat(TEXT("SOS_TargetDistance"));
	//UE_LOG(LogTemp, Display, TEXT("Distance is %f"), TargetDistance);

	// MoveTo를 구현
	
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("SOS_TargetActor"))); // SOS_TargetActor 가져오기
	AActor* SelfActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("SOS_SelfActor")));     // SOS_SelfActor 가져오기
	
	if (AIController && TargetActor)
	{
		// AIController의 MoveTo 명령 실행
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(TargetActor);            // 목표 설정
		MoveRequest.SetAcceptanceRadius(100.0f);         // 목표 도달 반경 설정
		MoveRequest.SetUsePathfinding(true);             // 경로 탐색 활성화

		FNavPathSharedPtr NavPath;                       // 경로 정보 저장 (선택 사항)
		EPathFollowingRequestResult::Type MoveResult = AIController->MoveTo(MoveRequest, &NavPath);

		// 로그 출력
		switch (MoveResult)
		{
		case EPathFollowingRequestResult::AlreadyAtGoal:
			UE_LOG(LogTemp, Display, TEXT("AI is already at the target!"));
			break;
		case EPathFollowingRequestResult::RequestSuccessful:
			UE_LOG(LogTemp, Display, TEXT("MoveTo request successful."));
			break;
		case EPathFollowingRequestResult::Failed:
			UE_LOG(LogTemp, Error, TEXT("MoveTo request failed!"));
			break;
		}

		// 경로 디버깅 (선택 사항)
		if (NavPath && NavPath->GetPathPoints().Num() > 0)
		{
			for (const FNavPathPoint& Point : NavPath->GetPathPoints())
			{
				UE_LOG(LogTemp, Display, TEXT("Path Point: %s"), *Point.Location.ToString());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AIController or TargetActor is null!"));
	}
	
	// 조건: Distance가 NearDistance 보다 크면 몽타주 재생, 아니면 멈춤
	if (TargetDistance > NearDistance)
	{
		// 몽타주가 이미 재생 중이 아닌 경우에만 재생
		if (!bIsPlayingMontage && MontageToPlay)
		{
			ControlledCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
			bIsPlayingMontage = true;
		}
	}
	else
	{
		// 몽타주가 재생 중이면 정지
		if (bIsPlayingMontage && MontageToPlay)
		{
			ControlledCharacter->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, MontageToPlay);
			bIsPlayingMontage = false;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	// 몽타주 상태 확인
	if (bIsPlayingMontage && !ControlledCharacter->GetMesh()->GetAnimInstance()->Montage_IsPlaying(MontageToPlay))
	{
		bIsPlayingMontage = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


void USOS_BTT_DistanceMove::FinishTask(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type Result)
{
	FinishLatentTask(OwnerComp, Result);
}


