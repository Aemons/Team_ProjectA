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
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionObjectType(ECC_Pawn); // 충돌 채널 설정
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Pawn에 대해 Overlap 처리
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASOS_NiagaraActor::OnBoxComponentBeginOverlap);

	// Niagara Component 생성
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);

	// Niagara 시스템 종료 이벤트
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
	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			DamageValue,
			GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);

		UE_LOG(LogTemp, Log, TEXT("ASOS_NiagaraActor: Applied %f damage to %s"), DamageValue, *OtherActor->GetName());
	}
}

// Niagara System 종료 시 호출
void ASOS_NiagaraActor::OnNiagaraSystemFinished(UNiagaraComponent* PSystem)
{
	Destroy(); // Actor 삭제
}
