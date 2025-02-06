#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SOS_BoxCollisionActor.generated.h"

UCLASS()
class TEAM_PROJECTA_API ASOS_BoxCollisionActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASOS_BoxCollisionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Box Collision Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	// Damage Value to apply on overlap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageValue = 10.0f;

	
private:
	// Overlap event handler
	UFUNCTION()
	void OnBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
