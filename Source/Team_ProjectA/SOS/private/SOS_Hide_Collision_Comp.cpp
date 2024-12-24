// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_Hide_Collision_Comp.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"

// Sets default values for this component's properties
USOS_Hide_Collision_Comp::USOS_Hide_Collision_Comp()
{
	// 이 컴포넌트가 초기화 시 Tick하지 않도록 설정
	PrimaryComponentTick.bCanEverTick = false;

	// SphereCollision 컴포넌트 생성 및 초기화
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(300.0f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionSphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
}


// Called when the game starts
void USOS_Hide_Collision_Comp::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void USOS_Hide_Collision_Comp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USOS_Hide_Collision_Comp::AttachToBone(USkeletalMeshComponent* Mesh, FName BoneName)
{
	// 본에 부착
	if (CollisionSphere && Mesh)
	{
		// SnapToTargetIncludingScale: 본의 위치, 회전, 스케일을 따라감
		CollisionSphere->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, BoneName);
		UE_LOG(LogTemp, Warning, TEXT("Attached to Bone: %s"), *BoneName.ToString());
	}
	
}

void USOS_Hide_Collision_Comp::EnableCollision()
{
	if (CollisionSphere)
	{
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void USOS_Hide_Collision_Comp::DisableCollision()
{
	if (CollisionSphere)
	{
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void USOS_Hide_Collision_Comp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		// 충돌한 액터 처리
		UE_LOG(LogTemp, Warning, TEXT("Collision with %s"), *OtherActor->GetName());

		// 필요에 따라 플레이어 또는 특정 액터를 처리
		// APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	}
}

