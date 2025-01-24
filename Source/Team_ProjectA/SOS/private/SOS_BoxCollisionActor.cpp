#include "Team_ProjectA/SOS/public/SOS_BoxCollisionActor.h"

#include "JHS_C_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values
ASOS_BoxCollisionActor::ASOS_BoxCollisionActor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root Component 생성
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Box Collision 생성
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent); // 루트 컴포넌트에 부착
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // 충돌 활성화
	BoxCollision->SetGenerateOverlapEvents(true); // Overlap 이벤트 생성
	BoxCollision->SetCollisionObjectType(ECC_WorldDynamic); // 충돌 채널 설정
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 채널 무시
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Pawn에 대해서만 Overlap 처리

	// Overlap 이벤트 바인딩
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASOS_BoxCollisionActor::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ASOS_BoxCollisionActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASOS_BoxCollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Overlap 이벤트 처리
void ASOS_BoxCollisionActor::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// 유효성 검사: Overlapped Actor가 존재하고 자신이 아닌 경우에만 처리
	if (OtherActor && OtherActor != this)
	{
		// AJHS_C_Player 클래스의 액터인지 확인
		if (OtherActor->IsA(AJHS_C_Player::StaticClass()))
		{
			// 데미지를 적용
			UGameplayStatics::ApplyDamage(
				OtherActor,          // 피해를 받는 액터
				DamageValue,         // 데미지 값
				GetInstigatorController(), // 데미지를 준 컨트롤러
				this,                // 데미지를 준 액터
				UDamageType::StaticClass() // 데미지 타입
			);

			// 로그 출력
			UE_LOG(LogTemp, Log, TEXT("Spread Attack ASOS_BoxCollisionActor: Applied %f damage to %s"), DamageValue, *OtherActor->GetName());
		}
		else
		{
			// 플레이어가 아닌 액터에 대한 로그
			//UE_LOG(LogTemp, Warning, TEXT("ASOS_BoxCollisionActor: Skipped damage for non-player actor %s"), *OtherActor->GetName());
		}
	}
}
