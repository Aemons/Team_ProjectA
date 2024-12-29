#include "JHS_C_WeaponStructures.h"

#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"

//FMainActionData
void FMainActionData::AttackAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRate);
}
////////////////////////////////////////////////////////////////////