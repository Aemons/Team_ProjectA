#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "JHS_C_Notify_EndAction.generated.h"

UCLASS()
class TEAM_PROJECTA_API UJHS_C_Notify_EndAction : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
