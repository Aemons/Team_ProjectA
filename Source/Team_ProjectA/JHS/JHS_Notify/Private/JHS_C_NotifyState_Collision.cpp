#include "JHS_C_NotifyState_Collision.h"
#include "JHS_Global.h"

#include "JHS_C_WeaponComponent.h"
#include "JHS_C_Attachment.h"

FString UJHS_C_NotifyState_Collision::GetNotifyName_Implementation() const
{
    return "Collisions";
}

void UJHS_C_NotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
    CheckNull(weapon);
    CheckNull(weapon->GetAttachment());

    weapon->GetAttachment()->OnCollision();
}

void UJHS_C_NotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    UJHS_C_WeaponComponent* weapon = Cast<UJHS_C_WeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_WeaponComponent::StaticClass()));
    CheckNull(weapon);
    CheckNull(weapon->GetAttachment());

    weapon->GetAttachment()->OffCollision();
}
