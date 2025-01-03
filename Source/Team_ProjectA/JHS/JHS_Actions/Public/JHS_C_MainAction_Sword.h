#pragma once

#include "CoreMinimal.h"
#include "JHS_C_MainAction.h"
#include "JHS_C_MainAction_Sword.generated.h"

UCLASS()
class TEAM_PROJECTA_API UJHS_C_MainAction_Sword : public UJHS_C_MainAction
{
	GENERATED_BODY()

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	void MainAction() override;
	void Begin_MainAction() override;
	void End_MainAction() override;

public:
	void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuser, class ACharacter* InOther) override;
	void OnAttachmentEndCollision() override;

private:
	bool bEnable;
	bool bExist;

	int32 Index;

	TArray<class ACharacter*> Hitted;
};
