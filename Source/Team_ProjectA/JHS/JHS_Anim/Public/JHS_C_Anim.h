#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JHS_C_Anim.generated.h"

UCLASS()
class TEAM_PROJECTA_API UJHS_C_Anim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	float Direction = 0.0f;
};
