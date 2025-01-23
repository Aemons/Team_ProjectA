// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_Hide_Box_Comp.h"

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
		// 다른 액터와의 상호작용 로직을 여기서 구현
		UE_LOG(LogTemp, Warning, TEXT("SOS_Hide_Box_Comp: Overlapped with %s"), *OtherActor->GetName());
	}
}
