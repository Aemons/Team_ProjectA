// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"
#include "GameFramework/Pawn.h"

// 생성자
ASOS_AIController::ASOS_AIController(FObjectInitializer const& ObjectInitializer)
{
	
}

// AIController가 Pawn(캐릭트)를 소유할 때 호출되는 함수
void ASOS_AIController::OnPossess(APawn* InPawn)
{
	// 부모 클래스이 OnPossess 함수를 호출하여 기본적인 소유 로직을 처리
	Super::OnPossess(InPawn);

	// InPawn이 ASOS_BOSS_Character 클래스의 인스턴스인지 확인하고, 맞다면 ASOS_Boss_Character 변수에 캐스팅하여 할당
	if(ASOS_BOSS_Character* const SOS_Boss_Character = Cast<ASOS_BOSS_Character>(InPawn))
	{
		if(UBehaviorTree* const tree = SOS_Boss_Character->GetBehaviorTree())
		{
			UBlackboardComponent* b;

			UE_LOG(LogTemp, Warning, TEXT("ASOS_AIController::OnPossess"));
			
			UseBlackboard(tree->BlackboardAsset, b);

			// b를 현재 컨트롤러의 클랙보드로 설정
			Blackboard = b;

			// Behavior Tree 실행
			RunBehaviorTree(tree);
		}
		
	}
	
}

void ASOS_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Blackboard)
	{
		// TargetLocation과 SelfLocation 가져오기
		FVector TargetLocation = Blackboard->GetValueAsVector(TEXT("SOS_TargetLocation"));
		FVector SelfLocation = Blackboard->GetValueAsVector(TEXT("SOS_SelfLocation"));

		// 거리 계산
		float Distance = FVector::Dist(TargetLocation, SelfLocation);

		// Blackboard에 거리 값 저장
		Blackboard->SetValueAsFloat(DistanceKey, Distance);

		// 디버그 로그 출력
		//UE_LOG(LogTemp, Warning, TEXT("Distance between Target and Self: %f"), Distance);
	}
}
