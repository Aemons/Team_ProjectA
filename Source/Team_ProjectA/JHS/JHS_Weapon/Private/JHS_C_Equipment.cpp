#include "JHS_C_Equipment.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

#include "JHS_C_StateComponent.h"
#include "JHS_C_MoveComponent.h"

void UJHS_C_Equipment::BeginPlay(ACharacter* InOwner, FEquipmentData& InData)
{
	OwnerChaeacter = InOwner;
	Data = InData;

	StateComp = Cast<UJHS_C_StateComponent>(OwnerChaeacter->GetComponentByClass(UJHS_C_StateComponent::StaticClass()));
	MoveComp = Cast<UJHS_C_MoveComponent>(OwnerChaeacter->GetComponentByClass(UJHS_C_MoveComponent::StaticClass()));

	bEquipped = false;
}

void UJHS_C_Equipment::Equip()
{
	StateComp->SetEquipMode();

	if (OnEquipmentEquip.IsBound())
		OnEquipmentEquip.Broadcast();
	
	if (Data.bUseControllerRotation)
		MoveComp->EnableControlRotation();
	
	if (!!Data.Montage && StateComp->IsActionMode() == false)
		OwnerChaeacter->PlayAnimMontage(Data.Montage, Data.PlayRate);
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void UJHS_C_Equipment::Unequip()
{
	bEquipped = false;
	MoveComp->DisableControlRotation();

	if (OnEquipmentUnequip.IsBound())
		OnEquipmentUnequip.Broadcast();
}

void UJHS_C_Equipment::Begin_Equip()
{
	bBeginEquip = true;

	if (OnEquipmentBeginEquip.IsBound())
		OnEquipmentBeginEquip.Broadcast();
}

void UJHS_C_Equipment::End_Equip()
{
	bBeginEquip = false;
	bEquipped = true;

	StateComp->SetIdleMode();

	if (OnEquipmentEndEquip.IsBound())
		OnEquipmentEndEquip.Broadcast();
}