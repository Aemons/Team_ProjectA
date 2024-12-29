#include "JHS_C_MainAction.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

#include "JHS_C_MoveComponent.h"
#include "JHS_C_StateComponent.h"

#include "JHS_C_Attachment.h"
#include "JHS_C_Equipment.h"

UJHS_C_MainAction::UJHS_C_MainAction()
{
}

void UJHS_C_MainAction::BeginPlay(AJHS_C_Attachment* InAttachment, UJHS_C_Equipment* InEquipment, ACharacter* InOwner, const TArray<FMainActionData>& InMainActionData)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	StateComp = Cast<UJHS_C_StateComponent>(OwnerCharacter->GetComponentByClass(UJHS_C_StateComponent::StaticClass()));
	MoveComp = Cast<UJHS_C_MoveComponent>(OwnerCharacter->GetComponentByClass(UJHS_C_MoveComponent::StaticClass()));

	MainActionDatas = InMainActionData;
}

void UJHS_C_MainAction::MainAction()
{
	bInAction = true;
	StateComp->SetActionMode();
}

void UJHS_C_MainAction::Begin_MainAction()
{
	bBeginAction = true;
}

void UJHS_C_MainAction::End_MainAction()
{
	bInAction = false;
	bBeginAction = false;

	StateComp->SetIdleMode();
}
