#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JHS_C_WeaponStructures.h"

#include "JHS_C_MainAction.generated.h"

UCLASS(Abstract, NotBlueprintable)
class TEAM_PROJECTA_API UJHS_C_MainAction : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }
	FORCEINLINE bool GetInAction() { return bInAction; }

public:
	UJHS_C_MainAction();

	virtual void BeginPlay
	(
		class AJHS_C_Attachment* InAttachment,
		class UJHS_C_Equipment* InEquipment,
		class ACharacter* InOwner,
		const TArray<FMainActionData>& InMainActionData
	);

	virtual void Tick(float InDeltaTime) {}

public:
	UFUNCTION()
	virtual void OnBegin_Equip() {}

	UFUNCTION()
	virtual void OnUnequip() {}

	UFUNCTION()
	virtual void OnAttachmentBeginCollision() {}

	UFUNCTION()
	virtual void OnAttachmentEndCollision() {}

	UFUNCTION()
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuser, class ACharacter* InOther) {}

	UFUNCTION()
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther) {}

public:
	virtual void MainAction();
	virtual void Begin_MainAction();
	virtual void End_MainAction();

protected:
	bool bBeginAction;
	bool bInAction;

	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UJHS_C_MoveComponent* MoveComp;
	class UJHS_C_StateComponent* StateComp;

	TArray<FMainActionData> MainActionDatas;
};
