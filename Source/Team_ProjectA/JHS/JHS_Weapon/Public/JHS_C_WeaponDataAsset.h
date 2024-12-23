#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "JHS_C_WeaponStructures.h"

#include "JHS_C_WeaponDataAsset.generated.h"

UCLASS()
class TEAM_PROJECTA_API UJHS_C_WeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class AJHS_C_Attachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UJHS_C_Equipment* GetEquipment() { return Equipment; }

private://Weapon Class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AJHS_C_Attachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJHS_C_Equipment> EquipmentClass;

private://Weapon Class Default Data Setting
	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
	TArray<FAttackActionData> AttackActionData;


private:
	UPROPERTY()
	class UJHS_C_Equipment* Equipment;

	UPROPERTY()
	class AJHS_C_Attachment* Attachment;

public:
	UJHS_C_WeaponDataAsset();
	void BeginPlay(class ACharacter* InOwner);
};
