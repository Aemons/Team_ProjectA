// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "SOS_Hide_SphereComp.h"
#include "GameFramework/Actor.h"
#include "SOS_Hide_baby.generated.h"

UCLASS()
class TEAM_PROJECTA_API ASOS_Hide_baby : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASOS_Hide_baby();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collision Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USOS_Hide_SphereComp* BabyCollision;

	// 투사체의 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 1500.0f;

	// 포물선 효과를 위한 곡선 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Gravity = FVector(0.0f, 0.0f, -150.0f);

	// 투사체 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale")
	FVector Hide_Baby_Scale = FVector(0.2f, 0.2f, 0.2f);

	// 투사체 회전
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	FRotator Hide_Baby_Rotate = FRotator(0.0f, 0.0f, 0.0f);

	// 나이아가라 효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* NiagaraEffect;

	// 데미지 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Baby_Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundBase*> ImpactSounds;
	
private:
	// 루트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;

	// 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* Mesh;

	// 현재 속도
	FVector Velocity;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
