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
			//�浹�� �߻��� OverlappedComponent�� ��ġ�� ����
			FVector ImpactLocation = OverlappedComponent->GetComponentLocation();
			//����� ���� ��ġ
			FVector ClosestBoneLocation;
			//�ּҰŸ�
			float MinDistance = FLT_MAX;

			//��� ĳ������ ��� ���� �̸��� ������ (���� ����)
			const TArray<FName>& BoneNames = OtherMesh->GetAllSocketNames();

			for (const FName& BoneName : BoneNames)
			{
				FVector BoneLocation = OtherMesh->GetBoneLocation(BoneName);

				//���� ��ġ�� �浹��ġ�� �Ÿ��� ���
				float Distance = FVector::Dist(ImpactLocation, BoneLocation);

				//���� ����� ���� ��ġ�� ã���� ��ġ, �̸� ����
				if (Distance < MinDistance)
				{
					MinDistance = Distance;
					ClosestBoneLocation = BoneLocation;
				} 
			}

			//Impact Effect, Sound Transform �Ҵ� �� ����
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
	//ImpactEffect ���� ���
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

