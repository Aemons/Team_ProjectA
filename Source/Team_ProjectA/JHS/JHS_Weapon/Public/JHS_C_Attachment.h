#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JHS_C_Attachment.generated.h"

//NotifyState_Collision Call Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentBeginCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentEndCollision);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, AActor*, InAttackCuser, class ACharacter*, InOther);
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

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public://Collision On/Off
	void OnCollision();
	void OffCollision();

public://Delegate Value
	//Collision Delegate Value
	FAttachmentBeginCollision OnAttachmentBeginCollision;
	FAttachmentEndCollision OnAttachmentEndCollision;

	//Overlap Delegate Value
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FAttachmentEndOverlap OnAttachmentEndOverlap;


};
