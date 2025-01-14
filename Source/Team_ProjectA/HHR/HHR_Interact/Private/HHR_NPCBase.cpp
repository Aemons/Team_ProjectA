// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_NPCBase.h"

#include "JHS_C_Player.h"
#include "Components/SphereComponent.h"
#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractComponent.h"


// Sets default values
AHHR_NPCBase::AHHR_NPCBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components 생성 & 할당 
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(150.0);
	//
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh Comp"));
	SkeletalMeshComp->SetupAttachment(SphereCollision);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if(skeletalMeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(skeletalMeshAsset.Object);
	}
	SkeletalMeshComp->SetRelativeLocation(FVector(0, 0, -100.f));
	SkeletalMeshComp->SetRelativeRotation(FRotator(0, -90, 0));
	
}

// Called when the game starts or when spawned
void AHHR_NPCBase::BeginPlay()
{
	Super::BeginPlay();

	// Overlap 바인딩 
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHHR_NPCBase::OnComponentBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AHHR_NPCBase::OnComponentEndOverlap);
}

// Called every frame
void AHHR_NPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHHR_NPCBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// PlayerCharacter의 forward vector를 이용해서 UI 여부 결정 & flag 설정 
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap"));
	AJHS_C_Player* playerCharacter = Cast<AJHS_C_Player>(OtherActor);
	if(playerCharacter && DoesFaceToCh(OtherActor))
	{
		// TODO : UI 띄우기
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UI띄움"));
		playerCharacter->GetInteractComp()->SetDoesIntearct(true);
	}
	else
	{
		// TODO : UI 꺼주기
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UI꺼줌"));
		playerCharacter->GetInteractComp()->SetDoesIntearct(false);
	}
	
}

void AHHR_NPCBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// TODO : UI 꺼주고 CantInteract() 실행
	AJHS_C_Player* playerCharacter = Cast<AJHS_C_Player>(OtherActor);
	if(playerCharacter)
	{
		// TODO : UI 꺼주기
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UI꺼줌"));
		playerCharacter->GetInteractComp()->SetDoesIntearct(false);
	}
}

void AHHR_NPCBase::Interact()
{
	// 부모 구현 아직 필요 없음  
}

bool AHHR_NPCBase::DoesFaceToCh(AActor* OtherActor)
{
	// TODO : 충돌한 actor의 Forward vector를 이요해서 방향 판단하여 UI 띄울 수 있는지 판별
	// 캐릭터의 반대 방향이여야 함 
	FVector npcForward = GetActorForwardVector() * -1;
	FVector chForward = OtherActor->GetActorForwardVector();

	float dotProduct = FVector::DotProduct(npcForward, chForward);

	float degree = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, (TEXT("%f"), degree));
	
	return false;
}

