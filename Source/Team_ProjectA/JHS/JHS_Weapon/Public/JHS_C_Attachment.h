#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JHS_C_Attachment.generated.h"

//NotifyState_Collision Call Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentBeginCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentEndCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, AActor*, InAttackCuaser, class ACharacter*, InOther);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttachmentEndOverlap, class ACharacter*, InAttacker, class ACharacter*, InOther);

UCLASS()
class TEAM_PROJECTA_API AJHS_C_Attachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Root;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	class ACharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TArray<class UShapeComponent*> Collisions;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impact Effect")
	class UFXSystemAsset* ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impact Effect")
	FRotator ImpactEffectRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impact Effect")
	FVector ImpactEffectScale = FVector(1.0, 1.0, 1.0);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impact Sound")
	class USoundBase* ImpactEffectSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impact Sound")
	class USoundBase* ImpactWeaponSound;

//Default Function
/////////////////////////////////////////////////////////////////////////////
public:	
	AJHS_C_Attachment();

protected:
	virtual void BeginPlay() override;
/////////////////////////////////////////////////////////////////////////////

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnBeginEquip();
	virtual void OnBeginEquip_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
	void OnEndEquip();
	virtual void OnEndEquip_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
	void OnUnequip();
	virtual void OnUnequip_Implementation() {};

protected:
	UFUNCTION(BlueprintCallable, Category = "Attach")
	void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable, Category = "Attach")
	void AttachToCollision(FName InCollisionName);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public://Collision On/Off
	void OnCollision();
	void OffCollision();

private:
	void PlayEffect(FTransform& InTransform);
	void PlaySound(FTransform& InTransform);

public://Delegate Value
	//Collision Delegate Value
	FAttachmentBeginCollision OnAttachmentBeginCollision;
	FAttachmentEndCollision OnAttachmentEndCollision;

	//Overlap Delegate Value
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FAttachmentEndOverlap OnAttachmentEndOverlap;

private:
	FTransform transform;
};
