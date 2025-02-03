#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SOS_BTT_IncreaseSpeed.generated.h"

/**
 * A behavior tree task to increase the character's speed and update a Blackboard key.
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTT_IncreaseSpeed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	// 생성자
	USOS_BTT_IncreaseSpeed();

protected:
	// 태스크 실행 시 호출
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	// 스피드 증가 배율
	UPROPERTY(EditAnywhere, Category = "Task Settings")
	float SpeedMultiplier = 1.8f;

	// SOS_Status에 저장할 값 (Blackboard Key)
	UPROPERTY(EditAnywhere, Category = "Task Settings")
	FName StatusKeyName = "SOS_State";

	UPROPERTY(EditAnywhere, Category = "Task Settings")
	FName TargetKeyName = "Target"; // 캐릭터의 위치를 가져올 Key (선택 사항)
};
