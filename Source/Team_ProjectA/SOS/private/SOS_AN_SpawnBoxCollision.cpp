#include "Team_ProjectA/SOS/public//SOS_AN_SpawnBoxCollision.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void USOS_AN_SpawnBoxCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !BoxCollisionActorClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("USOS_AN_SpawnBoxCollision: Invalid MeshComp or BoxCollisionActorClass."));
		return;
	}

	// 소유자 액터 가져오기
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("USOS_AN_SpawnBoxCollision: OwnerActor is null."));
		return;
	}

	// 소켓 위치와 회전 가져오기
	FVector SocketLocation = MeshComp->GetSocketLocation(NAME_None); // 기본 소켓 사용
	FRotator SocketRotation = MeshComp->GetSocketRotation(NAME_None);

	// 위치와 회전에 오프셋 추가
	FVector SpawnLocation = SocketLocation + SocketRotation.RotateVector(LocationOffset);
	FRotator SpawnRotation = SocketRotation + RotationOffset;

	// Actor 스폰 파라미터 설정
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// BoxCollisionActor 스폰
	AActor* SpawnedActor = MeshComp->GetWorld()->SpawnActor<AActor>(BoxCollisionActorClass, SpawnLocation, SpawnRotation, SpawnParams);

	// Box 크기 설정
	if (SpawnedActor)
	{
		UBoxComponent* BoxComponent = SpawnedActor->FindComponentByClass<UBoxComponent>();
		if (BoxComponent)
		{
			BoxComponent->SetBoxExtent(BoxSize); // 크기 설정
			//UE_LOG(LogTemp, Log, TEXT("USOS_AN_SpawnBoxCollision: Set Box Size to %s."), *BoxSize.ToString());
		}

		//UE_LOG(LogTemp, Log, TEXT("USOS_AN_SpawnBoxCollision: Spawned BoxCollisionActor at %s."), *SpawnLocation.ToString());

		// Destroy 타이머 설정
		FTimerHandle DestroyTimerHandle;
		MeshComp->GetWorld()->GetTimerManager().SetTimer(
			DestroyTimerHandle,
			[SpawnedActor]() {
				if (IsValid(SpawnedActor) && !SpawnedActor->IsActorBeingDestroyed())
				{
					SpawnedActor->Destroy();
					//UE_LOG(LogTemp, Log, TEXT("USOS_AN_SpawnBoxCollision: Destroyed BoxCollisionActor."));
				}
			},
			DestroyDelay,
			false // 반복하지 않음
		);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("USOS_AN_SpawnBoxCollision: Failed to spawn BoxCollisionActor."));
	}
}
