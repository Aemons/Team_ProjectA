// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_NPCBase.h"

#include "Components/SphereComponent.h"


// Sets default values
AHHR_NPCBase::AHHR_NPCBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components 생성 & 할당 
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh Comp"));
	SetRootComponent(SkeletalMeshComp);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if(skeletalMeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(skeletalMeshAsset.Object);
	}
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(SkeletalMeshComp);
	SphereCollision->SetRelativeLocation(FVector(0, 0, 100.f));
	SphereCollision->SetSphereRadius(150.0);
	
}

// Called when the game starts or when spawned
void AHHR_NPCBase::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap;
	SphereCollision->OnComponentEndOverlap;

}

// Called every frame
void AHHR_NPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHHR_NPCBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO : PlayerCharacter의 forward vector를 이용해서 UI 여부 결정 & PlayerCharacter의 CanInteract() 함수 실행
	// TODO : UI 안켜지면 CantInteract() 실행 
	
}

void AHHR_NPCBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// TODO : UI 꺼주고 CantInteract() 실행 
}

void AHHR_NPCBase::Interact()
{
	// 부모 구현 아직 필요 없음  
}

