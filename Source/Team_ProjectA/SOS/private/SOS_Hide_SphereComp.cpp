// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_Hide_SphereComp.h"

#include "JHS_C_Player.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"

// 생성자
USOS_Hide_SphereComp::USOS_Hide_SphereComp()
{
	// 기본 충돌 설정
	InitSphereRadius(30.0f);  // 구체의 반경 설정 (필요에 따라 변경 가능)
	//SetCollisionProfileName(TEXT("OverlapAllDynamic"));  // 기본 충돌 프로파일 설정

	// Overlap 이벤트 활성화
	OnComponentBeginOverlap.AddDynamic(this, &USOS_Hide_SphereComp::OnOverlapBegin);

	// 초기에는 충돌 비활성화 (필요 시 활성화)
	UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// 본(Bone)에 부착
void USOS_Hide_SphereComp::AttachToBone(USkeletalMeshComponent* Mesh, FName BoneName)
{
	if (Mesh)
	{
		// 본에 컴포넌트 부착
		// SnapToTargetIncludingScale 규칙을 사용하여 본의 위치, 회전, 스케일에 정확히 맞춥니다.
		AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, BoneName);

		UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_SphereComp: Attached to Bone: %s"), *BoneName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("USOS_Hide_SphereComp: Mesh is null, cannot attach."));
	}
}

// 충돌 활성화
void USOS_Hide_SphereComp::EnableCollision()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // 충돌 활성화
	//UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_SphereComp: Collision Enabled"));
}

// 충돌 비활성화
void USOS_Hide_SphereComp::DisableCollision()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);  // 충돌 비활성화
	//UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_SphereComp: Collision Disabled"));
}

// Overlap 이벤트 처리 (다른 액터와 충돌했을 때 호출)
void USOS_Hide_SphereComp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		// AJHS_C_Player 클래스의 액터인지 확인
		if (OtherActor->IsA(AJHS_C_Player::StaticClass()))
		{
			UE_LOG(LogTemp, Log, TEXT("USOS_Hide_Box_Comp: Applied %f damage to %s"), SphereDamage, *OtherActor->GetName());
			
			// 데미지 적용
			UGameplayStatics::ApplyDamage(
				OtherActor,          // 피해를 받는 액터
				SphereDamage,         // 데미지 값 (멤버 변수로 설정)
				GetOwner()->GetInstigatorController(), // 데미지를 준 컨트롤러
				GetOwner(),          // 데미지를 준 액터
				UDamageType::StaticClass() // 데미지 타입
			);

			
			
			// 🔹 랜덤 사운드 재생
			if (ImpactSounds.Num() > 0)  // 배열이 비어있지 않은지 확인
			{
				int32 RandomIndex = FMath::RandRange(0, ImpactSounds.Num() - 1); // 랜덤 인덱스 선택
				USoundBase* RandomSound = ImpactSounds[RandomIndex];

				if (RandomSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, RandomSound, GetOwner()->GetActorLocation());
					UE_LOG(LogTemp, Warning, TEXT("Impact sound played: %s"), *RandomSound->GetName());
				}
			}
			
			DisableCollision();

			// 로그 출력
		}
		else
		{
			// 예외 처리: 플레이어가 아닌 액터에 대해 로그 출력
			//UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_Box_Comp: Skipped damage for non-player actor %s"), *OtherActor->GetName());
		}
	}

	
}
