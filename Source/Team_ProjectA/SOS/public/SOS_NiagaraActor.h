#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "SOS_NiagaraActor.generated.h"

UCLASS()
class TEAM_PROJECTA_API ASOS_NiagaraActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASOS_NiagaraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Box Collision Overlap 이벤트
	UFUNCTION()
	void OnBoxComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	// Niagara System 종료 시 호출
	UFUNCTION()
	void OnNiagaraSystemFinished(UNiagaraComponent* PSystem);

	// 일정 시간 후 BoxCollision을 활성화하는 함수
	void EnableCollision();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision; // Box Collision Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* NiagaraComponent; // Niagara Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageValue = 10.f; // 기본 데미지 값

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraSystem* NiagaraSystem; // Niagara 시스템

	/**  일정 시간 후 콜리전 활성화 딜레이 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	float CollisionActivationDelay = 0.5f; // 기본값 1.5초

private:
	/**  콜리전 활성화 타이머 핸들 */
	FTimerHandle CollisionTimerHandle;
};
