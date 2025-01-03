#include "JHS_C_NotifyState_MainAction.h"
#include "JHS_Global.h"

#include "JHS_C_WeaponComponent.h"
#include "JHS_C_MainAction_Sword.h"

FString UJHS_C_NotifyState_MainAction::GetNotifyName_Implementation() const
{
	return "MainAction_Combo";
}

void UJHS_C_NotifyState_MainAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	UJHS_C_MainAction_Sword* combo = Cast<UJHS_C_MainAction_Sword>(weapon->GetMainAction());
	CheckNull(combo);

	combo->EnableCombo();
}

void UJHS_C_NotifyState_MainAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	UJHS_C_MainAction_Sword* combo = Cast<UJHS_C_MainAction_Sword>(weapon->GetMainAction());
	CheckNull(combo);

	combo->DisableCombo();
}
