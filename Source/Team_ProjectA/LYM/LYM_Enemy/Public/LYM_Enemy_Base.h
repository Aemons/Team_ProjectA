// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LYM_Enemy_Base.generated.h"

UCLASS()
class TEAM_PROJECTA_API ALYM_Enemy_Base : public ACharacter
{
	GENERATED_BODY()
	//////////////////////// Variables //////////////////////////
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TArray<UAnimMontage*> Normal_R_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* ComboAttack_0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* ComboAttack_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* ComboAttack_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* RangeAttack_0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* RangeAttack_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	UAnimMontage* DashAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector CLocation;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Rate")
	float InPlayRate = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Rate")
	float InPlayRate_3 = 0.3f;
	
	//////////////////////// Function //////////////////////////
public:
	ALYM_Enemy_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
