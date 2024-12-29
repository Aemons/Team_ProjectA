#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

public:
	void AttackAction(class ACharacter* InOwner);


};

UCLASS()
class TEAM_PROJECTA_API UJHS_C_WeaponStructures : public UObject
{
	GENERATED_BODY()
	
};
