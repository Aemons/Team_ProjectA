#include "JHS_C_MainAction_Sword.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"
#include "JHS_C_StateComponent.h"
#include "JHS_C_MoveComponent.h"

void UJHS_C_MainAction_Sword::MainAction()
{
	CheckTrue(MainActionDatas.Num() < 1);

	if (bEnable)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	CheckFalse(StateComp->IsIdleMode());
	
	Super::MainAction();
	
	MoveComp->EnableControlRotation();
	MainActionDatas[Index].AttackAction(OwnerCharacter);
}

void UJHS_C_MainAction_Sword::Begin_MainAction()
{
	Super::Begin_MainAction();
	CheckFalse(bExist);


	bExist = false;
	MainActionDatas[++Index].AttackAction(OwnerCharacter);
}

void UJHS_C_MainAction_Sword::End_MainAction()
{
	Super::End_MainAction();

	MoveComp->DisableControlRotation();
	Index = 0;
}

void UJHS_C_MainAction_Sword::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuser, InOther);
	CheckNull(InOther);

	for (ACharacter* hitted : Hitted)
		CheckTrue(hitted == InOther);

	Hitted.AddUnique(InOther);


	//일반몬스터가 있을경우 HitMontage에 대한 로직설정
}

void UJHS_C_MainAction_Sword::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	//HitData에 대한 후처리 로직설정 가능 (있으면)
	Hitted.Empty();
}
