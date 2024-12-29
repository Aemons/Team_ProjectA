#include "JHS_C_Notify_EndAction.h"
#include "JHS_Global.h"

#include "JHS_C_WeaponComponent.h"
#include "JHS_C_MainAction.h"

FString UJHS_C_Notify_EndAction::GetNotifyName_Implementation() const
{
    return "End_MainAction";
}

void UJHS_C_Notify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
    CheckNull(weapon);
    CheckNull(weapon->GetMainAction());

    weapon->GetMainAction()->End_MainAction();
}
