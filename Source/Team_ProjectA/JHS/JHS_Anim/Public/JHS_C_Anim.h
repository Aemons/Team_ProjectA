#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JHS_C_Anim.generated.h"

UCLASS()
class TEAM_PROJECTA_API UJHS_C_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	FVector2D PlayerMovementInput = FVector2D::ZeroVector;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bPlayerRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	class AJHS_C_Player* OwnerCharacter;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void PlayerSpeed();
	void PlayerDirection();

	void ShouldMove();
	void Falling();

private:
	FRotator PrevRotation;


};
