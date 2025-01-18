// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HHR_InteractComponent.generated.h"

// 입력 바인딩

// ** Interact Comp **
// ActorComp + object channel (Interact : NPC)
// (LineTrace or collision)
// * LineTrace : (0.2s 혹은 몇초) 동안 계속해서 앞에 interact할 actor 있는지 체크
//  - 있으면 UI 띄우고 -> flag 세팅
//		- flag 있는 상태에서 입력 받으면 InteractInterface의 Interact() 실행
// * Collision
// - 부모의 Capsule collision에 beginoverlap end overlap 시 flag setting 


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAM_PROJECTA_API UHHR_InteractComponent : public UActorComponent
{
	GENERATED_BODY()

/////////////////////////////////////////////////////////////////////////
// ** FORCEINLINE 함수 **
public:
	FORCEINLINE bool GetDoesIntearct() const {return bDoesInteract;}
	FORCEINLINE void SetDoesIntearct(bool b) {bDoesInteract = b;}
	

/////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = "Interact Input")
	class UInputAction* IA_Interact;
	

/////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수 ** 
public:
	// Sets default values for this component's properties
	UHHR_InteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	virtual void InitializeComponent() override;

/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	// Player의 델리게이트에 바인딩할 함수
	void SetUpInputBinding(class UEnhancedInputComponent* Input);
	// IA에 바인딩할 함수
	void Interact();

	// *Interact*
	void InteractOn(AActor* OtherActor);
	void InteractOff(AActor* OtherActor);


/////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
private:
	TObjectPtr<class AJHS_C_Player> OwnerCharacter;


private: //*Interact*
	// Interact 할 수 있는지 체크해주는 변수 
	bool bDoesInteract = false;
	// Interact Actor
	TObjectPtr<class AActor> InteractActor = nullptr;

};
