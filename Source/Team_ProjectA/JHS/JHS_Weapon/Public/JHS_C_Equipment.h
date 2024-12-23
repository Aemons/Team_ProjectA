#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "JHS_C_WeaponStructures.h"

#include "JHS_C_Equipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBeginEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentEndEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentUnequip);

UCLASS()
class TEAM_PROJECTA_API UJHS_C_Equipment : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }

protected:
	UPROPERTY(BlueprintReadOnly)
	class ACharacter* OwnerChaeacter;

public:
	void BeginPlay(ACharacter* InOwner, FEquipmentData& InData);

public:
	void Equip();
	void Unequip();

	void Begin_Equip();
	void End_Equip();

public:
	FEquipmentEquip OnEquipmentEquip;
	FEquipmentBeginEquip OnEquipmentBeginEquip;
	FEquipmentEndEquip OnEquipmentEndEquip;
	FEquipmentUnequip OnEquipmentUnequip;

private:
	bool bBeginEquip;
	bool bEquipped;

	FEquipmentData Data;

	class UJHS_C_StateComponent* StateComp;
	class UJHS_C_MoveComponent* MoveComp;
};
