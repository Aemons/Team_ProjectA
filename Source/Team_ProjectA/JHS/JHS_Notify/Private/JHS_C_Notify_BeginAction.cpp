#include "JHS_C_Notify_BeginAction.h"
#include "JHS_Global.h"

#include "JHS_C_WeaponComponent.h"
#include "JHS_C_MainAction.h"

FString UJHS_C_Notify_BeginAction::GetNotifyName_Implementation() const
{
	return "Begin_MainAction";
}

void UJHS_C_Notify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
	CheckNull(weapon);
	CheckNull(weapon->GetMainAction());

	weapon->GetMainAction()->Begin_MainAction();
}
