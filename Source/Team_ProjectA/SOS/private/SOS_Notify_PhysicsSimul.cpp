// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/SOS/public/SOS_Notify_PhysicsSimul.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void USOS_Notify_PhysicsSimul::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("SimulatePhysicsNotify: MeshComp or Owner is null"));
		return;
	}

	// Physics Simulation 활성화
	MeshComp->SetSimulatePhysics(true);

	// 캐릭터의 Movement Component 비활성화
	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->DisableMovement();
	}

	UE_LOG(LogTemp, Log, TEXT("Physics Simulation enabled for: %s"), *MeshComp->GetName());
}
