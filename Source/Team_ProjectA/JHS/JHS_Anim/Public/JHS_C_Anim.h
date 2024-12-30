#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "JHS_C_WeaponComponent.h"

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
	float ForwardInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	float RightInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	EWeaponType WeaponType = EWeaponType::Max;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bPlayerRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bPlayerDodge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Check Value")
	class AJHS_C_Player* OwnerCharacter;

//Default Function
//////////////////////////////////////////////////////////////////////
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
//////////////////////////////////////////////////////////////////////

private:
	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	void PlayerSpeed();
	void PlayerRun();
	void PlayerDodge();
	void PlayerDirection();
	void PlayerMovementInputVector();

	void ShouldMove();
	void Falling();

private:
	FRotator PrevRotation;
	class UCharacterMovementComponent* MovementComp;
	class UJHS_C_WeaponComponent* WeaponComp;
	


};
