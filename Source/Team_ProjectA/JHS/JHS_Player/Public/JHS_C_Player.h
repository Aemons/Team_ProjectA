#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "JHS_C_WeaponComponent.h"
 
#include "JHS_C_Player.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindDelegate, class UEnhancedInputComponent*);

UCLASS()
class TEAM_PROJECTA_API AJHS_C_Player : public ACharacter
{
	GENERATED_BODY()

public:
	FORCEINLINE class USpringArmComponent* GetSpringArmComp() const { return SpringArmComp; }
	FORCEINLINE class UCameraComponent* GetCameraComp() const { return CameraComp; }
	FORCEINLINE FVector2D GetMovementInput() { return MovementInput; }
	FORCEINLINE EWeaponType GetPlayerWeaponType() { return WeaponType; }

	FORCEINLINE bool GetPlayerRun() { return bIsPlayerRun; }
	FORCEINLINE bool GetPlayerDodge() { return bIsPlayerDodge; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View Limit")
	FVector2D PitchViewLimit = FVector2D(-50, +50);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Input")
	FVector2D MovementInput;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Type")
	EWeaponType WeaponType = EWeaponType::Max;

public: //Max/Current Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth = 0.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge Value")
	float DodgeDelay = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge Value")
	bool bIsPlayerDodge = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge Montage")
	TArray<class UAnimMontage*> DodgeMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dodge Montage")
	float DodgeMontage_PlayRate = 1.0f;

public: //Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* CameraComp;

public://Actor Component
	UPROPERTY(VisibleAnywhere, Category = "Actor Component")
	class UJHS_C_MoveComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, Category = "Actor Component")
	class UJHS_C_StateComponent* StateComp;

	UPROPERTY(VisibleAnywhere, Category = "Actor Component")
	class UJHS_C_WeaponComponent* WeaponComp;

public: //InputMapping & Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Run;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction")
	class UInputAction* IA_Player_Dodge;

	

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
	void Player_OnDodge();
	void Player_OffDodge();

	void PlayerBrakingWalkingValue();

public:
	FInputBindDelegate OnInputBindDelegate;

protected:
	
	FVector2D LookInput = FVector2D::ZeroVector;

	bool bIsPlayerRun = false;

	FTimerHandle BrakingWalkingHandle;
	FTimerHandle OffDodgeHandle;
};
