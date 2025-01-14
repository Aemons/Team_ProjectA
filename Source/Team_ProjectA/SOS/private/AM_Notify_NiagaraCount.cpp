// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/AM_Notify_NiagaraCount.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

void UAM_Notify_NiagaraCount::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !Template)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Custom Notify: UAM_Notify_NiagaraCount triggered."));

	// 나이아가라 효과 생성
	UFXSystemComponent* NiagaraComp = SpawnEffect(MeshComp, Animation);
	if (NiagaraComp)
	{
		UWorld* World = MeshComp->GetWorld();
		if (World)
		{
			// 일정 시간 후 나이아가라 제거
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(
				TimerHandle,
				[NiagaraComp]()
				{
					if (NiagaraComp)
					{
						NiagaraComp->Deactivate();  // 먼저 비활성화
						NiagaraComp->DestroyComponent();  // 이후 삭제

						UE_LOG(LogTemp, Warning, TEXT("Niagara effect Destroyed."));
					}
				},
				DestroyDelay,
				false
			);
		}
	}
}
