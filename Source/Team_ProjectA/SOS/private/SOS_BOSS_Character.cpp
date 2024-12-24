// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"
#include "Components/SphereComponent.h"
#include "ClassViewerModule.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ASOS_BOSS_Character::ASOS_BOSS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메쉬 초기화
	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/00_Project/00_Asset/Enemy/Hideoplast/Meshes/SK_Hideoplast.SK_Hideoplast'"));

	if(InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);

		//Relate -> 상대적 위치값, 회전값
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(-4, 0, -90));
		
	}

	
	
	// 오른손 구체 컴포넌트 생성
	RightHandCollision = CreateDefaultSubobject<USOS_Hide_SphereComp>(TEXT("RightHandCollision"));
	RightHandCollision->SetupAttachment(GetMesh());  // Mesh에 부착

	// 왼손 구체 컴포넌트 생성
	LeftHandCollision = CreateDefaultSubobject<USOS_Hide_SphereComp>(TEXT("LeftHandCollision"));
	LeftHandCollision->SetupAttachment(GetMesh());  // Mesh에 부착
	
	
}

// Called when the game starts or when spawned
void ASOS_BOSS_Character::BeginPlay()
{
	Super::BeginPlay();

	
	
	if (GetMesh())
	{
		// 본에 구체 컴포넌트 부착
		RightHandCollision->AttachToBone(GetMesh(), TEXT("Hideoplast_-R-Finger01Socket"));
		LeftHandCollision->AttachToBone(GetMesh(), TEXT("Hideoplast_-L-Finger01Socket"));

		// 충돌 활성화
		RightHandCollision->EnableCollision();
		LeftHandCollision->EnableCollision();
	}
	
}

// Called every frame
void ASOS_BOSS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASOS_BOSS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ASOS_BOSS_Character::GetBehaviorTree()
{
	return Tree;
}

