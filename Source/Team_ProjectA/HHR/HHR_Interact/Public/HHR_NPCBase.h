// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HHR_InteractInterface.h"
#include "GameFramework/Actor.h"
#include "HHR_NPCBase.generated.h"

UCLASS()
class TEAM_PROJECTA_API AHHR_NPCBase : public AActor, public IHHR_InteractInterface
{
	GENERATED_BODY()


/////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
protected:	// *Components*
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USphereComponent* SphereCollision;
	
	
/////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수 **
public:
	// Sets default values for this actor's properties
	AHHR_NPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

/////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **
private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:		// *InteractInterface
	virtual void Interact() override;

private:	// *내부에서 사용하는 함수
	bool DoesFaceToCh(AActor* OtherActor);
	
	
	
	
};

