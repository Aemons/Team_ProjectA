#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SOS_BTT_PlayOnce.generated.h"

UCLASS()
class TEAM_PROJECTA_API USOS_BTT_PlayOnce : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USOS_BTT_PlayOnce();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	// 애니메이션 몽타주를 한 번만 실행하기 위한 플래그
	bool bHasPlayedMontage = false;

	// 애니메이션 몽타주
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* MontageToPlay;

	// Behavior Tree Component 참조 (Task 종료를 위해 필요)
	UBehaviorTreeComponent* OwnerComponent;

	// 몽타주가 끝났는지 확인하기 위한 콜백
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
