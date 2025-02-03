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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision; // Box Collision Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* NiagaraComponent; // Niagara Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageValue = 50.f; // 기본 데미지 값

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraSystem* NiagaraSystem; // Niagara 시스템
};
