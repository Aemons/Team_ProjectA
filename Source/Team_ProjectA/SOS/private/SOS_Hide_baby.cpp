#include "Team_ProjectA/SOS/public/SOS_Hide_baby.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASOS_Hide_baby::ASOS_Hide_baby()
{
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 설정
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Skeletal Mesh 컴포넌트 생성 및 루트에 부착
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	// 메시 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/00_Project/00_Asset/Enemy/Hideoplast/Meshes/SK_Hideoplast.SK_Hideoplast"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetSkeletalMesh(MeshAsset.Object);
	}

	// 메시 크기 조정
	Mesh->SetRelativeScale3D(Hide_Baby_Scale);

	// 충돌 초기화
	Mesh->SetCollisionProfileName(TEXT("Projectile"));

	// 메시 기본 회전
	Mesh->SetRelativeRotation(Hide_Baby_Rotate);
}

// Called when the game starts or when spawned
void ASOS_Hide_baby::BeginPlay()
{
	Super::BeginPlay();

	// 초기 속도 설정 (Forward Vector 기준)
	Velocity = GetActorForwardVector() * Speed;
}

// Called every frame
void ASOS_Hide_baby::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 포물선 운동 처리
	Velocity += Gravity * DeltaTime;
	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;
	SetActorLocation(NewLocation);
}
