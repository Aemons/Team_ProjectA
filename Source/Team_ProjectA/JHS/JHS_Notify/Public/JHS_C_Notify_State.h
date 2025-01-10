#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "JHS_C_Notify_State.generated.h"

UENUM()
enum class EStateActionType : uint8
{
	Idle, Equip, Hitted, Dead, Action, Dodge, Max
};

UCLASS()
class TEAM_PROJECTA_API UJHS_C_Notify_State : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "StateType")
	EStateActionType StateType;

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
