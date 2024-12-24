#include "JHS_C_NotifyState_Equip.h"
#include "JHS_Global.h"

#include "JHS_C_WeaponComponent.h"
#include "JHS_C_Equipment.h"

FString UJHS_C_NotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip_State";
}

void UJHS_C_NotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetEquipment());

	weapon->GetEquipment()->Begin_Equip();
	
}

void UJHS_C_NotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetEquipment());

	weapon->GetEquipment()->End_Equip();
}
