// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	// RightHandCollision 선언
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USOS_Hide_SphereComp* RightHandCollision;

	// LeftHandCollision 선언
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USOS_Hide_SphereComp* LeftHandCollision;
};

