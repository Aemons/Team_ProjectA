// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_AM_MoveToNotify.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

void USOS_AM_MoveToNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AM_MoveToNotify: Invalid MeshComp or Owner."));
		return;
	}

	ACharacter* BossCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (!BossCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AM_MoveToNotify: BossCharacter is invalid."));
		return;
	}

	// AIController 가져오기
	AAIController* AIController = Cast<AAIController>(BossCharacter->GetController());
	if (!AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AM_MoveToNotify: AIController not found."));
		return;
	}

	// Blackboard 컴포넌트 가져오기
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AM_MoveToNotify: BlackboardComponent not found."));
		return;
	}

	// Blackboard에서 TargetActor 가져오기
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey));
	if (!TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AM_MoveToNotify: TargetActor not found in Blackboard."));
		return;
	}

	// 현재 보스 위치
	FVector BossLocation = BossCharacter->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	// 플레이어와 보스의 거리 계산
	float DistanceToTarget = FVector::Dist(BossLocation, TargetLocation);

	// 너무 가까우면 이동하지 않음
	if (DistanceToTarget < MoveDistance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AM_MoveToNotify: Already close to target. No need to move."));
		return;
	}

	// AI 이동 실행 (Blackboard 기반)
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(TargetActor);
	MoveRequest.SetAcceptanceRadius(MoveDistance);

	FNavPathSharedPtr NavPath;
	AIController->MoveTo(MoveRequest, &NavPath);

	UE_LOG(LogTemp, Log, TEXT("SOS_AM_MoveToNotify: Boss moving towards target (Speed: %f, Distance: %f)"), MoveSpeed, MoveDistance);

	// 일정 시간이 지나면 이동 중단
	FTimerHandle MoveStopTimerHandle;
	BossCharacter->GetWorldTimerManager().SetTimer(
		MoveStopTimerHandle,
		[AIController]()
		{
			AIController->StopMovement();
			UE_LOG(LogTemp, Log, TEXT("SOS_AM_MoveToNotify: MoveTo stopped after duration."));
		},
		MoveDuration, // 지정된 시간 후 중단
		false
	);
}
