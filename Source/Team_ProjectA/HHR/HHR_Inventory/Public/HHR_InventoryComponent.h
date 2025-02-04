// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HHR_InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_PROJECTA_API UHHR_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()


/////////////////////////////////////////////////////////////////////////
// ** UPROPERTY 변수 **
private:
	// *Input Action*
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = "Inventory Input")
	class UInputAction* IA_Inventory;

	// *Inventory Widget Class*
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = "Inventory Widget")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	// *Render Target으로 보여주기 위한 Scenen Component*
	UPROPERTY(EditAnywhere, Category = "Inventory Scene Component")
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, Category = "Inventory Scene Component")
	class USceneCaptureComponent2D* CaptureComp;

	// *Render Target*
	UPROPERTY(EditDefaultsOnly, Category = "Render Target")
	class UTextureRenderTarget2D* Wardrobe;
	
/////////////////////////////////////////////////////////////////////////
// ** 기본 생성 함수 ** 
public:	
	// Sets default values for this component's properties
	UHHR_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	// *player Character에 바인딩 
	virtual void InitializeComponent() override;

	


/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	// Player의 델리게이트에 바인딩할 함수
	void SetUpInputBinding(class UEnhancedInputComponent* Input);
	// IA에 바인딩할 함수
	void OpenInventory();


/////////////////////////////////////////////////////////////////////////
// ** 내부 멤버 변수 **
private:	//*소유하고 있는 Ch*
	TObjectPtr<class AJHS_C_Player> OwnerCharacter;
	
private:
	// Wardrobe 변수, widget
	TObjectPtr<class UHHR_Inventory> InventoryWidget;
	TObjectPtr<AActor> WardrobeActor;

	// 오픈되어 있는지 체크
	bool bIsOpen = false;
	
		
};
