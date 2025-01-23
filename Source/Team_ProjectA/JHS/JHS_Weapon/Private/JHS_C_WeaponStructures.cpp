#include "JHS_C_WeaponStructures.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"

//FMainActionData
void FMainActionData::AttackAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}

void FMainActionData::SendDamage(float Damage, ACharacter* InAttacker, AActor* InAttackCuser, ACharacter* InOther)
{
	FActionDamageEvent DamageEvent;
	DamageEvent.ActionDamageEvent = this;


	InOther->TakeDamage((Damage * Damagemultiplier), DamageEvent, InAttacker->GetController(), InAttackCuser);
}

void FMainActionData::PlayerCameraShake(UObject* InObject)
{
	if (CameraShakeClass)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(InObject, 0))
		{
			PC->ClientStartCameraShake(CameraShakeClass);
		}
	}
}
////////////////////////////////////////////////////////////////////