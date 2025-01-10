#include "JHS_C_Notify_State.h"
#include "JHS_Global.h"

#include "JHS_C_StateComponent.h"

FString UJHS_C_Notify_State::GetNotifyName_Implementation() const
{
	return "State";
}

void UJHS_C_Notify_State::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UJHS_C_StateComponent* state = Cast<UJHS_C_StateComponent>(MeshComp->GetOwner()->GetComponentByClass(UJHS_C_StateComponent::StaticClass()));
	CheckNull(state);

	switch (StateType)
	{
	case EStateActionType::Idle:
		state->SetIdleMode();
		break;
	case EStateActionType::Equip:
		state->SetEquipMode();
		break;
	case EStateActionType::Hitted:
		state->SetHittedMode();
		break;
	case EStateActionType::Dead:
		state->SetDeadMode();
		break;
	case EStateActionType::Action:
		state->SetActionMode();
		break;
	case EStateActionType::Dodge:
		state->SetDodgeMode();
		break;
	case EStateActionType::Max:
		break;
	default:
		break;
	}

}
