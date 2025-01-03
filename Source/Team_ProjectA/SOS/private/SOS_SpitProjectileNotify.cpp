#include "Team_ProjectA/SOS/public/SOS_SpitProjectileNotify.h"
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void USOS_SpitProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	// AI 캐릭터 가져오기
	AActor* AIActor = MeshComp->GetOwner();

	// 투사체 클래스 유효성 확인
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileClass is not set in Notify!"));
		return;
	}

	// 소켓 위치 및 방향 가져오기
	FVector SpawnLocation = MeshComp->GetSocketLocation(SpawnSocketName);

	// 플레이어 캐릭터 가져오기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(AIActor->GetWorld(), 0);

	// 플레이어가 없을 경우 기본 방향 설정 (방어 코드)
	FVector TargetLocation = PlayerCharacter ? PlayerCharacter->GetActorLocation() 
											 : (SpawnLocation + AIActor->GetActorForwardVector() * 3000);

	// 스폰 회전 계산
	FRotator SpawnRotation = (TargetLocation - SpawnLocation).Rotation();

	// 투사체 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = AIActor;

	AActor* SpawnedProjectile = AIActor->GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedProjectile)
	{
		// 메시의 방향을 회전값에 맞춰 조정
		USkeletalMeshComponent* ProjectileMesh = Cast<USkeletalMeshComponent>(SpawnedProjectile->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		if (ProjectileMesh)
		{
			ProjectileMesh->SetWorldRotation(SpawnRotation);
			UE_LOG(LogTemp, Log, TEXT("Projectile rotated to %s"), *SpawnRotation.ToString());
		}

		UE_LOG(LogTemp, Log, TEXT("Projectile spawned at %s"), *SpawnLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn projectile!"));
	}
}
