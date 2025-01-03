// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Animation/AnimMontage.h"
#include "SOS_BTTask_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTTask_PlayMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	USOS_BTTask_PlayMontage();
	
	/** The animation montage to play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* MontageToPlay;

	/** Whether the task should wait for the montage to finish */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	bool bWaitForMontageToEnd;

protected:
	/** Start executing the task */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UBehaviorTreeComponent* CachedOwnerComp; // BehaviorTreeComponent 캐시
	
	/** Event triggered when the montage ends */
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
};
