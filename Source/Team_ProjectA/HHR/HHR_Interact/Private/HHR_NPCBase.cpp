// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_NPCBase.h"

#include "JHS_C_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	// TODO : UI 세팅
	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget Comp"));
	InteractWidgetComp->SetupAttachment(SphereCollision);
	//
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm Comp"));
	SpringArmComp->SetupAttachment(SphereCollision);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
}

// Called when the game starts or when spawned
void AHHR_NPCBase::BeginPlay()
{
	Super::BeginPlay();

	// Overlap 바인딩 
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHHR_NPCBase::OnComponentBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AHHR_NPCBase::OnComponentEndOverlap);

	// Setting
	InteractWidgetComp->SetVisibility(false);
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
	if(playerCharacter)
	{
		playerCharacter->InteractOnMessage(this);
		// UI 표시
		InteractWidgetComp->SetVisibility(true);
		bIsWidgetOn = true;
	}
	
}

void AHHR_NPCBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJHS_C_Player* playerCharacter = Cast<AJHS_C_Player>(OtherActor);
	if(playerCharacter)
	{
		playerCharacter->InteractOffMessage(this);
		// UI 표시
		InteractWidgetComp->SetVisibility(false);
		bIsWidgetOn = false;
	}
}

void AHHR_NPCBase::Interact()
{
	// TODO : 자식에서 구현해줘야 함
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NPC 상호작용!"));
	//GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this);
}

// 일단 안씀...
bool AHHR_NPCBase::DoesFaceToCh(AActor* OtherActor)
{
	// 충돌한 actor의 Forward vector를 이요해서 방향 판단하여 UI 띄울 수 있는지 판별
	FVector npcForward = GetActorForwardVector() * -1;
	FVector chForward = OtherActor->GetActorForwardVector();

	float dotProduct = FVector::DotProduct(npcForward, chForward);

	float degree = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("%.2f"), degree));
	
	return false;
}

