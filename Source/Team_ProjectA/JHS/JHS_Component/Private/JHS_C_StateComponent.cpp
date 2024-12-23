#include "JHS_C_StateComponent.h"

UJHS_C_StateComponent::UJHS_C_StateComponent()
{
}

void UJHS_C_StateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UJHS_C_StateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UJHS_C_StateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UJHS_C_StateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UJHS_C_StateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UJHS_C_StateComponent::SetDodgeMode()
{
	ChangeType(EStateType::Dodge);
}

void UJHS_C_StateComponent::ChangeType(EStateType InType)
{
	EStateType PrevType = InType;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(PrevType, Type);
}

