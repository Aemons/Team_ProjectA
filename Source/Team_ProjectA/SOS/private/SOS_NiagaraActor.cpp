#include "Team_ProjectA/SOS/public/SOS_NiagaraActor.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASOS_NiagaraActor::ASOS_NiagaraActor()
{
	// Actor Tick 설정
	PrimaryActorTick.bCanEverTick = true;

	// Root Component 생성
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Niagara Component 생성
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent); // 루트 컴포넌트에 부착
	NiagaraComponent->SetRelativeLocation(FVector::ZeroVector); // 기본 위치 설정
	
	// Overlap 이벤트 바인딩
	NiagaraComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	NiagaraComponent->SetGenerateOverlapEvents(true);
	NiagaraComponent->OnComponentBeginOverlap.AddDynamic(this, &ASOS_NiagaraActor::OnNiagaraActorBeginOverlap);
}

// Called when the game starts or when spawned
void ASOS_NiagaraActor::BeginPlay()
{
	Super::BeginPlay();

	// 나이아가라 시스템 설정 및 활성화
	if (NiagaraSystem)
	{
		NiagaraComponent->SetAsset(NiagaraSystem); // 시스템 설정
		NiagaraComponent->Activate();             // 나이아가라 활성화
	}
}

// Called every frame
void ASOS_NiagaraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Overlap 이벤트 처리
void ASOS_NiagaraActor::OnNiagaraActorBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, 
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
		// 데미지를 적용
		UGameplayStatics::ApplyDamage(
			OtherActor,          // 피해를 받는 액터
			DamageValue,         // 데미지 값
			GetInstigatorController(), // 데미지를 준 컨트롤러
			this,                // 데미지를 준 액터
			UDamageType::StaticClass() // 데미지 타입
		);

		UE_LOG(LogTemp, Log, TEXT("ASOS_NiagaraActor: Applied %f damage to %s"), DamageValue, *OtherActor->GetName());
	}
}
