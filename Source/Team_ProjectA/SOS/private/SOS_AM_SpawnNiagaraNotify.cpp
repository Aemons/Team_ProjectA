#include "Team_ProjectA/SOS/public/SOS_AM_SpawnNiagaraNotify.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

void USOS_AM_SpawnNiagaraNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !NiagaraActorClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("USOS_AM_SpawnNiagaraNotify: Invalid MeshComp or NiagaraActorClass."));
		return;
	}

	// 소유자 액터 가져오기
	AActor* OwnerActor = MeshComp->GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("USOS_AM_SpawnNiagaraNotify: OwnerActor is null."));
		return;
	}

	// 소켓 위치와 회전 가져오기
	FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);
	FRotator SocketRotation = MeshComp->GetSocketRotation(SocketName);

	// 위치와 회전에 오프셋 추가
	FVector SpawnLocation = SocketLocation + SocketRotation.RotateVector(LocationOffset);
	FRotator SpawnRotation = SocketRotation + RotationOffset;

	// 액터 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor; // 소유자 설정
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 항상 스폰

	AActor* SpawnedActor = MeshComp->GetWorld()->SpawnActor<AActor>(NiagaraActorClass, SpawnLocation, SpawnRotation, SpawnParams);

	// 스폰 성공 여부 확인
	if (SpawnedActor)
	{
		UE_LOG(LogTemp, Log, TEXT("USOS_AM_SpawnNiagaraNotify: Niagara Actor spawned at %s."), *SpawnLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USOS_AM_SpawnNiagaraNotify: Failed to spawn Niagara Actor."));
	}
}
