// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"
#include "JHS_Global.h"

#include "AIController.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ClassViewerModule.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/SOS/public/SOS_Hide_Box_Comp.h"

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

	// Mesh 콜리전 설정
	

	// Mesh의 Overlap 이벤트 바인딩
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ASOS_BOSS_Character::OnMeshOverlapBegin);

	// 오른손 구체 컴포넌트 생성
	RightHandCollision = CreateDefaultSubobject<USOS_Hide_SphereComp>(TEXT("RightHandCollision"));
	RightHandCollision->SetupAttachment(GetMesh());  // Mesh에 부착

	// 왼손 구체 컴포넌트 생성
	LeftHandCollision = CreateDefaultSubobject<USOS_Hide_SphereComp>(TEXT("LeftHandCollision"));
	LeftHandCollision->SetupAttachment(GetMesh());  // Mesh에 부착

	BodyCollision = CreateDefaultSubobject<USOS_Hide_Box_Comp>(TEXT("BodyCollision"));
	BodyCollision->SetupAttachment(GetMesh());  // Mesh에 부착
	
	
}

// Called when the game starts or when spawned
void ASOS_BOSS_Character::BeginPlay()
{
	Super::BeginPlay();

	
	if (GetMesh())
	{
		// 본에 구체 컴포넌트 부착
		RightHandCollision->AttachToBone(GetMesh(), RightHandSoketName);
		LeftHandCollision->AttachToBone(GetMesh(), LeftHandSoketName);
		BodyCollision->AttachToBone(GetMesh(), BodySoketName);
		
		// 비충돌 활성화
		RightHandCollision->DisableCollision();
		LeftHandCollision->DisableCollision();
		BodyCollision->DisableCollision();

		/*
		// 충돌 활성화
		RightHandCollision->EnableCollision();
		LeftHandCollision->EnableCollision();
		BodyCollision->EnableCollision();
		*/
		
	}

	CurrentHP = MaxHP;
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

/*
void ASOS_BOSS_Character::TakeDamage(float DamageAmount)
{
	CurrentHP -= DamageAmount;

	if( CurrentHP <= (MaxHP*0.3) && Brust) // 30% 이하일 시 Burst 상태 변경
	{ // 더 작으면 최대 HP에서
		UE_LOG(LogTemp, Warning, TEXT("Boss is Burst!"));
		UE_LOG(LogTemp, Warning, TEXT("Boss took damage! Current HP: %f , MaxHP %f"), CurrentHP, MaxHP);
		
		SetBBEnumState(2);
		// 중복 처리
		Brust = false;
		
	}
	else if (CurrentHP <= 0.0f) // 보스의 체력이 0 이하가 된다면 Death 상태 변경
	{
		CurrentHP = 0.0f;
		UE_LOG(LogTemp, Warning, TEXT("Boss is Dead!"));
        
		SetBBEnumState(1);
		
	}

}
*/

void ASOS_BOSS_Character::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
		return;
	if(OtherComp)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Boss overlapped with %s"), *OtherActor->GetName());
		
	}

	// 데미지 처리 (예: 10의 고정 데미지)
	//TakeDamage(10.0f);
}


//void ASOS_BOSS_Character::TakeDamage(float DamageAmount)
//{
//	// 체력 감소
//	CurrentHP -= DamageAmount;
//
//	if( CurrentHP <= (MaxHP*0.3) && Brust) // 30% 이하일 시 Burst 상태 변경
//	{ // 더 작으면 최대 HP에서
//		
//		SetBBEnumState(2);
//		// 중복 처리
//		Brust = false;
//		
//	} // 체력이 0 이하라면 사망 처리
//	else if(CurrentHP <= 0.0f)
//	{
//		CurrentHP = 0.0f;
//		SetBBEnumState(1);
//
//		bIsDead = true;
//
//		// 여기에 사망 처리 로직 추가 (예: 애니메이션 재생)
//	}
//}

// ApplyDamage 시스템이 호출될 때 실행
float ASOS_BOSS_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser
)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력 감소
	CurrentHP -= DamageAmount;

	if (CurrentHP <= 0.0f)
	{
		//CurrentHP = 0.0f;
		SetBBEnumState(1);

		bIsDead = true;
		// 여기에 사망 처리 로직 추가 (예: 애니메이션 재생)
	}
	else if (CurrentHP <= (MaxHP * 0.3) && Brust) // 30% 이하일 시 Burst 상태 변경
	{ // 더 작으면 최대 HP에서

		SetBBEnumState(2);
		// 중복 처리
		Brust = false;

	} // 체력이 0 이하라면 사망 처리
	
	return	CurrentHP;
}

void ASOS_BOSS_Character::SetBBEnumState(int32 EnumNumber)
{
	// 추가 행동 (예: 보스 사망 처리)
	ACharacter* BossCharacter = Cast<ACharacter>(UGameplayStatics::GetActorOfClass(this, ASOS_BOSS_Character::StaticClass()));
	// Get AI Controller of Boss Character
	AAIController* BossAIController = Cast<AAIController>(BossCharacter->GetController());
	if (BossAIController && BossAIController->GetBlackboardComponent())
	{
		// Set Blackboard Key Value
		BossAIController->GetBlackboardComponent()->SetValueAsEnum("SOS_State", EnumNumber);
		//UE_LOG(LogTemp, Warning, TEXT("Blackboard Key '%s' updated to Enum Value '%d'."), *BlackboardKeyName.ToString(), EnumNumber);

		// 현재 실행중인 Task를 실패로 판단
		UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BossAIController->GetBrainComponent());
		if (BehaviorTreeComponent)
		{
			//BehaviorTreeComponent->RequestExecution(EBTNodeResult::Succeeded);
			BehaviorTreeComponent->StopTree(EBTStopMode::Safe); // 현재 작업을 안전하게 중단
			BehaviorTreeComponent->RestartTree(); // 트리를 다시 평가


			//UE_LOG(LogTemp, Warning, TEXT("Behavior Tree Task marked as failed."));
		}
            
	}

	// HHR
	// ----------------------------------------------------------------------------
	// UI 끄기
	if(BossHPWidget)
	{
		BossHPWidget->RemoveFromParent();
	}
	// ----------------------------------------------------------------------------
}


void ASOS_BOSS_Character::SetMontagePlayRate(float NewPlayRate)
{
	// 유효한 PlayRate인지 확인
	if (NewPlayRate <= 0.0f)
	{
		//UE_LOG(LogTemp, Error, TEXT("Invalid PlayRate: %f. PlayRate must be greater than 0."), NewPlayRate);
		return;
	}

	// 캐릭터의 AnimInstance 가져오기
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		//UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr for character %s"), *GetName());
		return;
	}

	// 현재 재생 중인 모든 몽타주에 대해 재생 속도 변경
	for (FAnimMontageInstance* MontageInstance : AnimInstance->MontageInstances)
	{
		if (MontageInstance)
		{
			MontageInstance->SetPlayRate(NewPlayRate);
		}
	}

	// 현재 재생 속도를 저장
	CurrentMontagePlayRate = NewPlayRate;

	//UE_LOG(LogTemp, Warning, TEXT("Montage PlayRate set to %f for character %s"), NewPlayRate, *GetName());
}

void ASOS_BOSS_Character::CreateBossHP()
{
	if(BossHPClass)
	{
		BossHPWidget = CreateWidget<UUserWidget>(GetWorld(), BossHPClass);
		BossHPWidget->AddToViewport();
	}
}
	


