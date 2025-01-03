// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SOS_SpitProjectileNotify.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_SpitProjectileNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// Notify 실행 시 호출되는 함수
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// 투사체 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	// 투사체 스폰 위치 (소켓 이름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName SpawnSocketName = TEXT("Hideoplast_-HeadSocket"); // 예: 오른손 소켓에서 투사체 발사
};
