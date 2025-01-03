#include "Team_ProjectA/SOS/public/SOS_AN_Collision_Hide_Enable.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"

void USOS_AN_Collision_Hide_Enable::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 기본 유효성 검사
	if (!MeshComp || !MeshComp->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AN_Collision_Hide_Enable: MeshComp or Owner is invalid."));
		return;
	}

	// 소유자 확인 (AI 캐릭터인지 확인)
	AActor* Owner = MeshComp->GetOwner();
	ASOS_BOSS_Character* BossCharacter = Cast<ASOS_BOSS_Character>(Owner);

	if (BossCharacter)
	{
		
		// LeftHandCollision과 RightHandCollision 활성화
		if (BossCharacter->LeftHandCollision)
		{
			BossCharacter->LeftHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//UE_LOG(LogTemp, Log, TEXT("Left hand collision enabled."));
		}

		if (BossCharacter->RightHandCollision)
		{
			BossCharacter->RightHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//UE_LOG(LogTemp, Log, TEXT("Right hand collision enabled."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AN_Collision_Hide_Enable: Owner is not a SOS_HIDE_BOSS_Char."));
	}
}
