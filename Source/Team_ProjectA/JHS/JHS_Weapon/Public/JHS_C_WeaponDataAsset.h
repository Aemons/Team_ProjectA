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
	FORCEINLINE class UJHS_C_MainAction* GetMainAction() { return MainAction; }

private://Weapon Class
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AJHS_C_Attachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJHS_C_Equipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UJHS_C_MainAction> MainActionClass;

private://Weapon Class Default Data Setting
	UPROPERTY(EditAnywhere)
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
	TArray<FMainActionData> MainActionData;

private:
	UPROPERTY()
	class AJHS_C_Attachment* Attachment;

	UPROPERTY()
	class UJHS_C_Equipment* Equipment;

	UPROPERTY()
	class UJHS_C_MainAction* MainAction;

public:
	UJHS_C_WeaponDataAsset();
	void BeginPlay(class ACharacter* InOwner);
};
