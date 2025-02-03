#include "Team_ProjectA/SOS/public/SOS_BoxCollContinuous.h"

#include "JHS_C_Player.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

// Sets default values
ASOS_BoxCollContinuous::ASOS_BoxCollContinuous()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root Component 생성
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Box Collision 생성
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionObjectType(ECC_WorldStatic);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Overlap 이벤트 바인딩
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASOS_BoxCollContinuous::OnBoxBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ASOS_BoxCollContinuous::OnBoxEndOverlap);
}

void ASOS_BoxCollContinuous::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Log, TEXT("Begin Play"));
	
	// AttachSocket이 NAME_None이 아니면 캐릭터의 소켓에 부착
	if (AttachSocket != "None")
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully attached to socket: "));
	
		// 소켓 이름에 해당하는 컴포넌트 찾기
		USkeletalMeshComponent* SkeletalMeshComp = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		// 유효성 검사
		if (SkeletalMeshComp)
		{
			// 소켓에 부착
			FName SocketName = AttachSocket; // AttachSocket에 설정된 소켓 이름
			this->AttachToComponent(SkeletalMeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);

			// 로그 출력
			UE_LOG(LogTemp, Log, TEXT("Successfully attached to socket: %s"), *SocketName.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to find a valid SkeletalMeshComponent to attach to."));
		}
	}
}

// Called every frame
void ASOS_BoxCollContinuous::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// 데미지 적용 함수
void ASOS_BoxCollContinuous::ApplyDamage()
{
	for (AActor* OverlappingActor : OverlappingActors)
	{
		// 유효한 액터인지 확인 (삭제된 액터는 아닐 경우)
		if (IsValid(OverlappingActor))
		{
			// 플레이어 캐릭터인지 확인
			if (OverlappingActor->IsA(AJHS_C_Player::StaticClass()))
			{
				UGameplayStatics::ApplyDamage(
					OverlappingActor,       // 피해를 받는 액터
					DamageValue,            // 데미지 값
					GetInstigatorController(), // 데미지를 준 컨트롤러
					this,                   // 데미지를 준 액터
					UDamageType::StaticClass() // 데미지 타입
				);

				UE_LOG(LogTemp, Log, TEXT("ASOS_BoxCollContinuous: Applied %f damage to %s"), DamageValue, *OverlappingActor->GetName());
			}
			else
			{
				// UE_LOG(LogTemp, Warning, TEXT("ASOS_BoxCollContinuous: Skipped damage to non-player character %s"), *OverlappingActor->GetName());
			}
		}
	}
}



// BeginOverlap 이벤트 처리
void ASOS_BoxCollContinuous::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// 유효성 검사 후 OverlappingActors에 추가
	if (OtherActor && OtherActor != this && !OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Add(OtherActor);

		// 타이머 시작
		if (!GetWorld()->GetTimerManager().IsTimerActive(DamageTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &ASOS_BoxCollContinuous::ApplyDamage, DamageInterval, true);
		}
	}
}

// EndOverlap 이벤트 처리
void ASOS_BoxCollContinuous::OnBoxEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	// OverlappingActors에서 제거
	if (OtherActor && OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Remove(OtherActor);

		// 타이머 중지 (더 이상 겹치는 액터가 없을 경우)
		if (OverlappingActors.Num() == 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		}
	}
}
