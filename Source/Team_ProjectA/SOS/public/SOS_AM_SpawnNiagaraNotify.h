#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SOS_AM_SpawnNiagaraNotify.generated.h"

/**
 * 애니메이션 노티파이: 나이아가라 액터를 스폰
 */
UCLASS()
class TEAM_PROJECTA_API USOS_AM_SpawnNiagaraNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 스폰할 Niagara Actor 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	TSubclassOf<AActor> NiagaraActorClass;

	// 스폰 위치 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	FVector LocationOffset;

	// 스폰 회전 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	FRotator RotationOffset;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	FName SocketName = NAME_None;
	
	// Notify 함수 오버라이드
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
