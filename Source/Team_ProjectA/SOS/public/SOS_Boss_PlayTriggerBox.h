#pragma once

#include "LevelSequence.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SOS_Boss_PlayTriggerBox.generated.h"

// 전방 선언
class AAIController;
class ALevelSequence;
class UBoxComponent;

UCLASS()
class TEAM_PROJECTA_API ASOS_Boss_PlayTriggerBox : public AActor
{
	GENERATED_BODY()

public:    
	// Sets default values for this actor's properties
	ASOS_Boss_PlayTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:    
	// Trigger Box Component
	UPROPERTY(EditAnywhere, Category = "Trigger")
	UBoxComponent* TriggerBox;

	// Name of the Blackboard Key to modify
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FName BlackboardKeyName = "SOS_State";

	// The Enum Value to set
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	uint8 EnumValueToSet = 0;
	// Example: Enum value for "Attack"
	// 0 Attack , 1 Death, 2 Burst, 3 stun, 4 Wait


	UFUNCTION()
	void OnSequenceFinished();
	
	// Overlap event handler
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// 재생할 Level Sequence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence")
	ULevelSequence* SequenceToPlay;
	
};
