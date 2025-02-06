#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SOS_AN_SpawnBoxCollision.generated.h"

UCLASS()
class TEAM_PROJECTA_API USOS_AN_SpawnBoxCollision : public UAnimNotify
{
	GENERATED_BODY()

public:
	// BoxCollisionActor의 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> BoxCollisionActorClass;

	// 스폰 위치 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVector LocationOffset;

	// 스폰 회전 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FRotator RotationOffset;

	// Box Collision의 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVector BoxSize = FVector(100.0f, 100.0f, 100.0f);

	// 스폰된 Actor의 파괴 대기 시간 (초 단위)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float DestroyDelay = 5.0f;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
