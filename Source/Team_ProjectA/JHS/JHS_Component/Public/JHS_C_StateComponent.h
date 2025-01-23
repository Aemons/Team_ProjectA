#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_C_StateComponent.generated.h"

UENUM()
enum class EStateType : uint8
{
	Idle = 0, Equip, Hitted, Dead, Action, Dodge, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_PROJECTA_API UJHS_C_StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsDodgeMode() { return Type == EStateType::Dodge; }

//Default Function
/////////////////////////////////////////////////////////////////////////////
public:	
	UJHS_C_StateComponent();

protected:
	virtual void BeginPlay() override;
/////////////////////////////////////////////////////////////////////////////

public://State Mode Function
	void SetIdleMode();
	void SetEquipMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetActionMode();
	void SetDodgeMode();

private:
	void ChangeType(EStateType InType);

public:
	FStateTypeChanged OnStateTypeChanged;

private:
	EStateType Type;
		
};
