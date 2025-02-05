// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SOS_AM_MoveToNotify.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_AM_MoveToNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// Notify 실행 시 호출되는 함수
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	/** 이동 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
	float MoveSpeed = 300.0f;

	/** 목표와의 도착 거리 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
	float MoveDistance = 150.0f;

	/** MoveTo 실행 지속 시간 (초) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveTo")
	float MoveDuration = 1.5f;

	/** 이동 목표를 가져올 Blackboard Key (ex: "SOS_TargetActor") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FName TargetActorKey = "SOS_TargetActor";
};
