// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
#include "HHR_ItemBase.generated.h"



// 실제 월드에 나타나는 item actor


UCLASS()
class TEAM_PROJECTA_API AHHR_ItemBase : public AActor
{
	GENERATED_BODY()

//////////////////////////////////////////////////////////////////////////////
// ** FORCEINLINE 함수 **
public:
	void SetItemData(FItemData* Data){ItemData = *Data;}
	FItemData* GetItemData() {return &ItemData;}


//////////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **

protected:
	// *Components*
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USphereComponent* SphereCollision;

	// *Color*
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	TArray<class UMaterialInterface*> ItemColors;

private:
	// *Data*
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), Category = "Data")
	FItemData ItemData;
	

//////////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수 **	
public:
	// Sets default values for this actor's properties
	AHHR_ItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

//////////////////////////////////////////////////////////////////////////////
// ** UFUNCTION 함수 **	
protected:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


//////////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **

public:
	// Item 색깔 setting
	void SetColor();


	
};
