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
		// 설정된 CollisionName에 따라 특정 충돌 컴포넌트를 비활성화
		if (CollisionName == FName("LeftHandCollision") && BossCharacter->LeftHandCollision)
		{
			BossCharacter->LeftHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//UE_LOG(LogTemp, Log, TEXT("Left hand collision enabled."));
		}
		else if (CollisionName == FName("RightHandCollision") && BossCharacter->RightHandCollision)
		{
			BossCharacter->RightHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//UE_LOG(LogTemp, Log, TEXT("Right hand collision enabled."));
		}
		else if(CollisionName == FName("BodyCollision") && BossCharacter->BodyCollision)
		{
			BossCharacter->BodyCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//UE_LOG(LogTemp, Log, TEXT("Body collision enabled."));
		}
		/*
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SOS_AN_Collision_Hide_Disable: CollisionName '%s' is invalid or component not found."),
				*CollisionName.ToString());
		}
		
	}
	
	else
		
	{
		UE_LOG(LogTemp, Warning, TEXT("SOS_AN_Collision_Hide_Enable: Owner is not a SOS_HIDE_BOSS_Char."));
	}
	*/
	}
}
