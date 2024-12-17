#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JHS_C_Player.generated.h"

UCLASS()
class TEAM_PROJECTA_API AJHS_C_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AJHS_C_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
