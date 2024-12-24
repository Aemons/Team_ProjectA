// Fill out your copyright notice in the Description page of Project Settings.

#include "Team_ProjectA/SOS/public/SOS_BTTask_PlayMontage.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"

// 생성자: 기본값 설정
USOS_BTTask_PlayMontage::USOS_BTTask_PlayMontage()
{
    NodeName = "Play Montage"; // Behavior Tree에서 노드 이름 설정
    bWaitForMontageToEnd = true; // 기본적으로 몽타주가 끝날 때까지 기다림
}

// Behavior Tree 태스크 실행 로직
EBTNodeResult::Type USOS_BTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Behavior Tree의 OwnerComp를 캐시로 저장 (나중에 사용)
    CachedOwnerComp = &OwnerComp;

    // AI Controller와 캐릭터 가져오기
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed; // AI Controller가 없으면 실패
    }

    // Boss 캐릭터 가져오기
    ASOS_BOSS_Character* ControlledCharacter = Cast<ASOS_BOSS_Character>(AIController->GetPawn());
    if (!ControlledCharacter || !MontageToPlay) // 캐릭터 또는 몽타주가 유효하지 않으면 실패
    {
        return EBTNodeResult::Failed;
    }

    // 캐릭터의 애니메이션 인스턴스 가져오기
    UAnimInstance* AnimInstance = ControlledCharacter->GetMesh()->GetAnimInstance();
    if (!AnimInstance) // AnimInstance가 없으면 실패
    {
        return EBTNodeResult::Failed;
    }

    // 몽타주 재생
    if (AnimInstance->Montage_Play(MontageToPlay))
    {
        if (bWaitForMontageToEnd) // 몽타주 종료를 기다릴 경우
        {
            // 몽타주 종료 시 호출될 델리게이트 추가
            AnimInstance->OnMontageEnded.AddDynamic(this, &USOS_BTTask_PlayMontage::OnMontageEnded);
            return EBTNodeResult::InProgress; // 태스크가 진행 중임을 알림
        }
        else
        {
            return EBTNodeResult::Succeeded; // 즉시 성공 처리
        }
    }

    return EBTNodeResult::Failed; // 몽타주 재생 실패
}

// 몽타주 종료 시 호출되는 함수
void USOS_BTTask_PlayMontage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    // 종료된 몽타주가 현재 실행 중인 태스크의 몽타주인지 확인
    if (Montage == MontageToPlay && CachedOwnerComp)
    {
        // 델리게이트 제거 (중복 호출 방지)
        AAIController* AIController = CachedOwnerComp->GetAIOwner();
        if (AIController)
        {
            ACharacter* ControlledCharacter = Cast<ACharacter>(AIController->GetPawn());
            if (ControlledCharacter)
            {
                UAnimInstance* AnimInstance = ControlledCharacter->GetMesh()->GetAnimInstance();
                if (AnimInstance)
                {
                    // 등록된 델리게이트를 해제
                    AnimInstance->OnMontageEnded.RemoveDynamic(this, &USOS_BTTask_PlayMontage::OnMontageEnded);
                }
            }
        }

        // 태스크 완료 처리 (성공 또는 중단에 따라 결과를 설정)
        FinishLatentTask(*CachedOwnerComp, bInterrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
    }
}
