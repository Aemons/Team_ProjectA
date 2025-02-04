// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_Hide_Box_Comp.h"

#include "JHS_C_Player.h"
#include "Kismet/GameplayStatics.h"

USOS_Hide_Box_Comp::USOS_Hide_Box_Comp()
{
	// BoxComponent의 크기를 매개변수로 설정
	InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	
	// Overlap 이벤트 활성화
	OnComponentBeginOverlap.AddDynamic(this, &USOS_Hide_Box_Comp::OnOverlapBegin);

	// 초기에는 충돌 비활성화 (필요 시 활성화)
	UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}

void USOS_Hide_Box_Comp::AttachToBone(USkeletalMeshComponent* Mesh, FName BoneName)
{
	if (Mesh)
	{
		// 본에 컴포넌트 부착
		// SnapToTargetIncludingScale 규칙을 사용하여 본의 위치, 회전, 스케일에 정확히 맞춥니다.
		AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, BoneName);

		UE_LOG(LogTemp, Warning, TEXT("SOS_Hide_Box_Comp: Attached to Bone: %s"), *BoneName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SOS_Hide_Box_Comp: Mesh is null, cannot attach."));
	}
}

void USOS_Hide_Box_Comp::EnableCollision()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // 충돌 활성화
	UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_SphereComp: Collision Enabled"));
}

void USOS_Hide_Box_Comp::DisableCollision()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);  // 충돌 비활성화
	UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_SphereComp: Collision Disabled"));
}

void USOS_Hide_Box_Comp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		// AJHS_C_Player 클래스의 액터인지 확인
		if (OtherActor->IsA(AJHS_C_Player::StaticClass()))
		{
			// 데미지 적용
			UGameplayStatics::ApplyDamage(
				OtherActor,          // 피해를 받는 액터
				BoxDamage,         // 데미지 값 (멤버 변수로 설정)
				GetOwner()->GetInstigatorController(), // 데미지를 준 컨트롤러
				GetOwner(),          // 데미지를 준 액터
				UDamageType::StaticClass() // 데미지 타입
			);

			DisableCollision();
			
			// 로그 출력
			UE_LOG(LogTemp, Log, TEXT("USOS_Hide_Box_Comp: Applied %f damage to %s"), BoxDamage, *OtherActor->GetName());
		}
		else
		{
			// 예외 처리: 플레이어가 아닌 액터에 대해 로그 출력
			UE_LOG(LogTemp, Warning, TEXT("USOS_Hide_Box_Comp: Skipped damage for non-player actor %s"), *OtherActor->GetName());
		}
	}

	
}
