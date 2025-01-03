#include "JHS_C_Attachment.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

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

	for (USceneComponent* Child : children)
	{
		UShapeComponent* Shape = Cast<UShapeComponent>(Child);

		if (!!Shape)
		{
			Shape->OnComponentBeginOverlap.AddDynamic(this, &AJHS_C_Attachment::OnComponentBeginOverlap);
			Shape->OnComponentEndOverlap.AddDynamic(this, &AJHS_C_Attachment::OnComponentEndOverlap);

			Collisions.Add(Shape);
		}
	}

	OffCollision();

	Super::BeginPlay();
}

void AJHS_C_Attachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void AJHS_C_Attachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, Cast<ACharacter>(OtherActor));
}

void AJHS_C_Attachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, Cast<ACharacter>(OtherActor));
}

void AJHS_C_Attachment::OnCollision()
{
	if (OnAttachmentBeginCollision.IsBound())
		OnAttachmentBeginCollision.Broadcast();
	
	for (UShapeComponent* Shape : Collisions)
		Shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AJHS_C_Attachment::OffCollision()
{
	if (OnAttachmentEndCollision.IsBound())
		OnAttachmentEndCollision.Broadcast();

	for (UShapeComponent* Shape : Collisions)
		Shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
