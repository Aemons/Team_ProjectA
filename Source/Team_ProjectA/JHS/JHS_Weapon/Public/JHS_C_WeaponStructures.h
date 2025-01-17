#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DamageEvents.h"

#include "JHS_C_WeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool bUseControllerRotation = true;
};

USTRUCT()
struct FMainActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
	float Power = 0.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

public:
	void AttackAction(class ACharacter* InOwner);
	void SendDamage(class ACharacter* InAttacker, AActor* InAttackCuser, ACharacter* InOther);
	void PlayerCameraShake(UObject* InObject);
};

USTRUCT()
struct FActionDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	FMainActionData* ActionDamageEvent;

};

UCLASS()
class TEAM_PROJECTA_API UJHS_C_WeaponStructures : public UObject
{
	GENERATED_BODY()
	
};
