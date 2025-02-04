#include "Team_ProjectA/SOS/public/SOS_NiagaraActor.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"

// Sets default values
ASOS_NiagaraActor::ASOS_NiagaraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root Component 생성
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Box Collision 생성
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 초기에 비활성화
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionObjectType(ECC_Pawn);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASOS_NiagaraActor::OnBoxComponentBeginOverlap);

	// Niagara Component 생성
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->OnSystemFinished.AddDynamic(this, &ASOS_NiagaraActor::OnNiagaraSystemFinished);
}

// Called when the game starts or when spawned
void ASOS_NiagaraActor::BeginPlay()
{
	Super::BeginPlay();

	// Niagara System 설정 및 활성화
	if (NiagaraSystem)
	{
		NiagaraComponent->SetAsset(NiagaraSystem);
		NiagaraComponent->Activate();
	}

	// 일정 시간이 지난 후 콜리전 활성화
	GetWorldTimerManager().SetTimer(CollisionTimerHandle, this, &ASOS_NiagaraActor::EnableCollision, CollisionActivationDelay, false);
}

// 일정 시간 후 콜리전 활성화
void ASOS_NiagaraActor::EnableCollision()
{
	if (BoxCollision)
	{
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		//UE_LOG(LogTemp, Warning, TEXT("ASOS_NiagaraActor: Collision Enabled!"));
	}
}

// Called every frame
void ASOS_NiagaraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Box Collision Overlap 이벤트 처리
void ASOS_NiagaraActor::OnBoxComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 유효한 액터인지 확인 & 자기 자신과 동일한 클래스인지 확인 (같은 나이아가라 액터끼리 충돌 방지)
	if (OtherActor && OtherActor != this && !OtherActor->IsA(ASOS_NiagaraActor::StaticClass()))
	{
		// Apply Damage 실행
		UGameplayStatics::ApplyDamage(
			OtherActor,
			DamageValue,
			GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);

		// 캐릭터 또는 적에게 피격된 경우 콜리전 비활성화
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("ASOS_NiagaraActor: Ignored collision with another NiagaraActor."));
	}
}

// Niagara System 종료 시 호출
void ASOS_NiagaraActor::OnNiagaraSystemFinished(UNiagaraComponent* PSystem)
{
	Destroy(); // Actor 삭제
}
