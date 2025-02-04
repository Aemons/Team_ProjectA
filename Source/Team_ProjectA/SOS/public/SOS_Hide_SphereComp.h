// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "SOS_Hide_SphereComp.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECTA_API USOS_Hide_SphereComp : public USphereComponent
{
	GENERATED_BODY()

	USOS_Hide_SphereComp();

public:
	
	// 본에 부착
	UFUNCTION(BlueprintCallable, Category="Collision")
	void AttachToBone(USkeletalMeshComponent* Mesh, FName BoneName);
	
	// 콜리전 활성화 함수
	UFUNCTION(BlueprintCallable, Category="Collision")
	void EnableCollision();

	// 콜리전 비활성화 함수
	UFUNCTION(BlueprintCallable, Category="Collision")
	void DisableCollision();

	// 콜리전 이벤트
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
