#include "Team_ProjectA/SOS/public/SOS_BTT_PlayOnce.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

USOS_BTT_PlayOnce::USOS_BTT_PlayOnce()
{
	NodeName = "Play Animation Once";
	bHasPlayedMontage = false;
	OwnerComponent = nullptr; // 초기화
}

EBTNodeResult::Type USOS_BTT_PlayOnce::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// AIController 가져오기
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	// 캐릭터 가져오기
	ACharacter* Character = Cast<ACharacter>(AIController->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	// 애니메이션 인스턴스 가져오기
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance || !MontageToPlay)
	{
		return EBTNodeResult::Failed;
	}

	// 몽타주가 이미 실행된 경우 성공으로 반환
	if (bHasPlayedMontage)
	{
		return EBTNodeResult::Succeeded;
	}

	// OwnerComponent 저장 (OnMontageEnded에서 사용)
	OwnerComponent = &OwnerComp;

	// 몽타주 종료 콜백 설정
	AnimInstance->OnMontageEnded.AddDynamic(this, &USOS_BTT_PlayOnce::OnMontageEnded);

	// 몽타주 실행
	AnimInstance->Montage_Play(MontageToPlay);
	bHasPlayedMontage = true;

	// 대기 중으로 설정 (Montage가 끝나면 콜백으로 완료 처리)
	return EBTNodeResult::InProgress;
}

void USOS_BTT_PlayOnce::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 지정된 몽타주가 끝났는지 확인
	if (Montage == MontageToPlay)
	{
		UE_LOG(LogTemp, Log, TEXT("Montage ended: %s"), *Montage->GetName());

		// OwnerComponent를 사용하여 Task 완료
		if (OwnerComponent)
		{
			FinishLatentTask(*OwnerComponent, EBTNodeResult::Succeeded);
		}
	}
}
