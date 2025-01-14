#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"
#include "AM_Notify_NiagaraCount.generated.h"

/**
 * 커스텀 애님 노티파이: 나이아가라 효과를 일정 시간 후 제거
 */
UCLASS()
class TEAM_PROJECTA_API UAM_Notify_NiagaraCount : public UAnimNotify_PlayNiagaraEffect
{
	GENERATED_BODY()

public:


	
	// 생성된 나이아가라 효과를 삭제할 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	float DestroyDelay = 3.0f; // 기본값 3초


	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
	
};
