// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SOS_AN_Collision_Hide_Enable.generated.h"

/**
 * AnimNotify to enable collision for left and right hand during an animation
 */
UCLASS()
class TEAM_PROJECTA_API USOS_AN_Collision_Hide_Enable : public UAnimNotify
{
	GENERATED_BODY()

protected:
	// 충돌 컴포넌트의 이름 (에디터에서 설정 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FName CollisionName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float setDamage = 10.0f;
	
	// 애니메이션 Notify 실행
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
