// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "SOS_Hide_Collision_Comp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_PROJECTA_API USOS_Hide_Collision_Comp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USOS_Hide_Collision_Comp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 콜리전 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	USphereComponent* CollisionSphere;

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
