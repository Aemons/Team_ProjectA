// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOS_Hide_Box_Comp.h"
#include "SOS_Hide_SphereComp.h"
#include "Components/SphereComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "SOS_BOSS_Character.generated.h"

UCLASS()
class TEAM_PROJECTA_API ASOS_BOSS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASOS_BOSS_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// BehaviorTree 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Behavior Tree Function
	UBehaviorTree* GetBehaviorTree();

	// RightHandCollision 선언
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USOS_Hide_SphereComp* RightHandCollision;

	// LeftHandCollision 선언
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USOS_Hide_SphereComp* LeftHandCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USOS_Hide_Box_Comp* BodyCollision;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FName RightHandSoketName = FName("Hideoplast_-R-Finger01Socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FName LeftHandSoketName = FName("Hideoplast_-L-Finger01Socket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FName BodySoketName = FName("Hideoplast_-L-Finger01Socket");
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Stats")
	float MaxHP = 100.0f;

	// HP 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Stats")
	float CurrentHP = MaxHP;
	
	// 데미지 처리 함수
	/*
	UFUNCTION(BlueprintCallable, Category = "Boss Stats")
	void TakeDamage(float DamageAmount);
	*/
	
	// ApplyDamage로 호출될 함수
	UFUNCTION()
	void TakeDamage(float DamageAmount);

	// 데미지를 받을 때 호출되는 함수 (ApplyDamage 사용)
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;


	// Name of the Blackboard Key to modify
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FName BlackboardKeyName = "SOS_State";
	
	
	// Example: Enum value for "Attack"
	// 0 Attack , 1 Death, 2 Burst, 3 stun, 4 Wait
	UFUNCTION()
	void SetBBEnumState(int32 EnumNumber);
	
	
private:
	// Mesh Overlap 처리 함수
	UFUNCTION()
	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool Brust = true;

public:
	// 몽타주 재생 속도를 변경하는 함수
	void SetMontagePlayRate(float NewPlayRate);

private:
	// 현재 재생 속도
	float CurrentMontagePlayRate = 1.0f; // 기본값 1.0
};

