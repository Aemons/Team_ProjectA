#include "JHS_C_Attachment.h"
#include "JHS_Global.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"

AJHS_C_Attachment::AJHS_C_Attachment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(Root);
}

void AJHS_C_Attachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);
	for (USceneComponent* child : children)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(child);

		if (!!shape)
		{
			shape->OnComponentBeginOverlap.AddDynamic(this, &AJHS_C_Attachment::OnComponentBeginOverlap);
			shape->OnComponentEndOverlap.AddDynamic(this, &AJHS_C_Attachment::OnComponentEndOverlap);

			Collisions.Add(shape);
		}
	}
	OffCollision();

	Super::BeginPlay();
}

//Attach Function
//////////////////////////////////////////////////////////////////////////////
void AJHS_C_Attachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void AJHS_C_Attachment::AttachToCollision(FName InCollisionName)
{
	for (UShapeComponent* collision : Collisions)
	{
		if (collision->GetName() == InCollisionName.ToString())
		{
			collision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InCollisionName);

			return;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////

//ComponentOverlap
//////////////////////////////////////////////////////////////////////////////
void AJHS_C_Attachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor), DamageCalculation(BaseDamage));

	if (ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor))
	{
		USkeletalMeshComponent* OtherMesh = OtherCharacter->GetMesh();

		if (!!OtherMesh)
		{
			//충돌이 발생한 OverlappedComponent의 위치를 저장
			FVector ImpactLocation = OverlappedComponent->GetComponentLocation();
			//가까운 본의 위치
			FVector ClosestBoneLocation;
			//최소거리
			float MinDistance = FLT_MAX;

			//대상 캐릭터의 모든 본의 이름을 가져옴 (소켓 포함)
			const TArray<FName>& BoneNames = OtherMesh->GetAllSocketNames();

			for (const FName& BoneName : BoneNames)
			{
				FVector BoneLocation = OtherMesh->GetBoneLocation(BoneName);

				//본의 위치와 충돌위치의 거리를 계산
				float Distance = FVector::Dist(ImpactLocation, BoneLocation);

				//가장 가까운 본의 위치를 찾으면 위치, 이름 저장
				if (Distance < MinDistance)
				{
					MinDistance = Distance;
					ClosestBoneLocation = BoneLocation;
				} 
			}

			//Impact Effect, Sound Transform 할당 및 설정
			transform.SetLocation(ClosestBoneLocation);
			transform.SetRotation(FQuat(ImpactEffectRotation));
			transform.SetScale3D(ImpactEffectScale);
			////////////////////////////////////////////////////////////////


		}//if(OtherMesh)

		PlayEffect(transform);
		PlaySound(transform);

	}//if(Cast OtherCharacter)
}

void AJHS_C_Attachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, Cast<ACharacter>(OtherActor));
}
//////////////////////////////////////////////////////////////////////////////

void AJHS_C_Attachment::OnCollision()
{
	if (OnAttachmentBeginCollision.IsBound())
		OnAttachmentBeginCollision.Broadcast();
	
	for (UShapeComponent* Shape : Collisions)
	{
		Shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Shape->SetCollisionProfileName(TEXT("OverlapAll"));
	}
}

void AJHS_C_Attachment::OffCollision()
{
	if (OnAttachmentEndCollision.IsBound())
		OnAttachmentEndCollision.Broadcast();

	for (UShapeComponent* Shape : Collisions)
	{
		Shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Shape->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

void AJHS_C_Attachment::PlayEffect(FTransform& InTransform)
{
	//ImpactEffect 있을 경우
	if (!!ImpactEffect)
	{
		if (UParticleSystem* Particle = Cast<UParticleSystem>(ImpactEffect))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InTransform);
		}

		if (UNiagaraSystem* Niagara = Cast<UNiagaraSystem>(ImpactEffect))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, InTransform.GetLocation(), (FRotator)InTransform.GetRotation(), InTransform.GetScale3D());
		}
	}
}

void AJHS_C_Attachment::PlaySound(FTransform& InTransform)
{
	//ImpactSound
	if (!!ImpactEffectSound)
	{
		if (USoundWave* SoundWave = Cast<USoundWave>(ImpactEffectSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundWave, InTransform.GetLocation());
		}

		if (USoundCue* SoundCue = Cast<USoundCue>(ImpactEffectSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, InTransform.GetLocation());
		}
	}

	//ImpactWeaponSound
	if (!!ImpactWeaponSound)
	{
		if (USoundWave* SoundWave = Cast<USoundWave>(ImpactWeaponSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundWave, InTransform.GetLocation());
		}

		if (USoundCue* SoundCue = Cast<USoundCue>(ImpactWeaponSound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, InTransform.GetLocation());
		}
	}
}

float AJHS_C_Attachment::DamageCalculation(float InDamage)
{
	bIsCriticalHit = false;

	float Max_Damage = BaseDamage * Max_DamageChance;
	float Min_Damage = BaseDamage * Min_DamageChance;

	float FinalDamage = FMath::RandRange(Min_Damage, Max_Damage);

	float Critical = FMath::RandRange(0.0, 1.0);

	if (Critical <= CriticalChance)
	{
		FinalDamage *= CriticalDamage;
		bIsCriticalHit = true;
	}
	
	return FinalDamage;
}

