#include "Team_ProjectA/SOS/public/SOS_BTTask_LookAtMoveTo.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

USOS_BTTask_LookAtMoveTo::USOS_BTTask_LookAtMoveTo()
{
    bNotifyTick = true;  // TickTask 활성화
    bIsMoving = false;
}

EBTNodeResult::Type USOS_BTTask_LookAtMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // AIController와 Blackboard 가져오기
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
    {
        return EBTNodeResult::Failed;
    }

    // 목표 위치 가져오기 (Blackboard의 키 이름은 "SOS_TargetLocation")
    TargetLocation = Blackboard->GetValueAsVector("SOS_TargetLocation");

    bIsMoving = true;

    return EBTNodeResult::InProgress;  // TickTask에서 계속 처리
}

void USOS_BTTask_LookAtMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    ACharacter* Character = Cast<ACharacter>(AIController->GetPawn());

    if (!AIController || !Character)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    // 목표 위치를 실시간으로 갱신
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        TargetLocation = Blackboard->GetValueAsVector("SOS_TargetLocation");
    }

    // 현재 위치와 목표 위치 계산
    FVector CurrentLocation = Character->GetActorLocation();
    float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

    // 목표를 바라보도록 회전 조정 (천천히 회전)
    FVector DirectionToTarget = (TargetLocation - CurrentLocation).GetSafeNormal();
    FRotator CurrentRotation = Character->GetActorRotation();
    FRotator TargetRotation = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();

    // 부드럽게 회전 (회전 속도 조정: 1.5f)
    FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 1.5f);
    Character->SetActorRotation(SmoothRotation);

    // 목표 방향과의 각도 차이를 계산
    float AngleDifference = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, TargetRotation.Yaw));

    // 각도 차이가 클 경우 MoveTo를 사용하지 않고 바라보는 방향으로 전진
    if (AngleDifference > 10.0f)  // 각도 차이가 10도 이상일 때
    {
        FVector ForwardDirection = Character->GetActorForwardVector();
        Character->AddMovementInput(ForwardDirection, 1.0f);  // 바라보는 방향으로 전진
    }
    else
    {
        // 각도 차이가 작으면 MoveTo를 사용하여 목표 위치로 이동
        if (bIsMoving)
        {
            AIController->MoveToLocation(TargetLocation);
        }
    }

    // 목표 위치에 도달하면 작업 종료
    if (DistanceToTarget < DistanceTarget)  // 목표 위치 근처로 간주
    {
        bIsMoving = false;
        AIController->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
