#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "JHS_C_Player.generated.h"

UCLASS()
class TEAM_PROJECTA_API AJHS_C_Player : public ACharacter
{
	GENERATED_BODY()

public:
	FORCEINLINE class USpringArmComponent* GetSpringArmComp() const { return SpringArmComp; }
	FORCEINLINE class UCameraComponent* GetCameraComp() const { return CameraComp; }

	FORCEINLINE FVector2D GetMovementInput() { return MovementInput; }

	FORCEINLINE bool GetPlayerRun() { return bIsPlayerRun; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View Limit")
	FVector2D PitchViewLimit = FVector2D(-50, +50);

public: //Max/Current Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 0.0f;

public: //Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* CameraComp;

public://Actor Component
	UPROPERTY(VisibleAnywhere, Category = "Actor Component")
	class UJHS_C_MoveComponent* MoveComp;

public: //InputMapping & Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Run;

//Defult Function
////////////////////////////////////////////////////////////////////////////////////
public:
	AJHS_C_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
////////////////////////////////////////////////////////////////////////////////////

private:
	void Player_Move(const FInputActionValue& InValue);
	void Player_Look(const FInputActionValue& InValue);
	void Player_OnRun();
	void Player_OffRun();

	void PlayerBrakingWalkingValue();

private:
	FVector2D MovementInput = FVector2D::ZeroVector;
	FVector2D LookInput = FVector2D::ZeroVector;

	bool bIsPlayerRun = false;

	FTimerHandle BrakingWalkingHandle;
};