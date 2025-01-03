// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Animation/AnimMontage.h"
#include "SOS_BTT_LookAtPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_BTT_LookAtPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USOS_BTT_LookAtPlayer();

protected:
	/** Called when the task is executed */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Called every tick while the task is running */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** Finish the task */
	void FinishTask(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type Result);

private:
	/** AI's rotation speed */
	UPROPERTY(EditAnywhere, Category = "LookAt")
	float RotationSpeed = 90.0f; // Degrees per second

	/** Montage to play */
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* MontageToPlay;

	/** Whether the montage is playing */
	bool bIsPlayingMontage = false;

	/** Player actor reference */
	AActor* PlayerActor;
	
};
