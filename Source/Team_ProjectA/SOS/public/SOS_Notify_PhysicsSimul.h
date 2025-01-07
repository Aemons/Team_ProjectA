// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SOS_Notify_PhysicsSimul.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_Notify_PhysicsSimul : public UAnimNotify
{
	GENERATED_BODY()

public:
	// Notify 실행 시 호출되는 함수
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
