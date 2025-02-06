#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SOS_BoxCollContinuous.generated.h"

UCLASS()
class TEAM_PROJECTA_API ASOS_BoxCollContinuous : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASOS_BoxCollContinuous();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Box Collision Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BoxCollision;

	// Damage value to apply per tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageValue = 10.0f;

	// Damage application interval (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageInterval = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FName AttachSocket = NAME_None;

	
private:
	// Timer handle for managing damage application
	FTimerHandle DamageTimerHandle;

	// Set of actors currently overlapping
	TSet<AActor*> OverlappingActors;

	// Apply damage to overlapping actors
	void ApplyDamage();

	// Event handlers for overlap
	UFUNCTION()
	void OnBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnBoxEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
