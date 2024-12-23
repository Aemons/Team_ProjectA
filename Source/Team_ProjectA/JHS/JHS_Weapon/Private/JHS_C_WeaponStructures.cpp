#include "JHS_C_WeaponStructures.h"

#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"

//FAttackActionData
void FAttackActionData::AttackAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}
////////////////////////////////////////////////////////////////////