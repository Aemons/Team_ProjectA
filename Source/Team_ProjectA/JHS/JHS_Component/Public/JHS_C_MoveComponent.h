#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_C_MoveComponent.generated.h"

UENUM()
enum class EWalkSpeedType : uint8
{
	Walk, Jog, Sprint, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_PROJECTA_API UJHS_C_MoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE EWalkSpeedType GetWalkType() {return Type;}

public:
	UPROPERTY(EditAnywhere, Category = "WalkSpeed")
	float PlayerSpeed[(int32)EWalkSpeedType::Max] = {200, 600, 800};

	UPROPERTY(EditAnywhere, Category = "Search")
	float SearchDistance = 1000.0f;

//Default Function
///////////////////////////////////////////////////////////////////////
public:	
	UJHS_C_MoveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
///////////////////////////////////////////////////////////////////////

public:
	UFUNCTION(BlueprintCallable)
	void SetWalk();

	UFUNCTION(BlueprintCallable)
	void SetJog();

	UFUNCTION(BlueprintCallable)
	void SetSprint();

	void SetWalkSpeed(EWalkSpeedType InType);

	void SearchEnemyTarget();

public:
	void EnableControlRotation();
	void DisableControlRotation();

private:
	class ACharacter* OwnerCharacter;
	EWalkSpeedType Type;

	bool bIsControlRotation;
};
