// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
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
	UPROPERTY(EditAnywhere, Category = "Inventory Scene Component")
	class USpotLightComponent* SpotLightComp;

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
// ** UFUNCTION 함수 **
public:
	// Inventory
	UFUNCTION()
	void ChangeArmor(class UHHR_ItemSlotTest* Armor);

private:
	UFUNCTION()
	void CloseInventory();



/////////////////////////////////////////////////////////////////////////
// ** 일반 함수 **
public:
	// Player의 델리게이트에 바인딩할 함수
	void SetUpInputBinding(class UEnhancedInputComponent* Input);
	// IA에 바인딩할 함수
	void OpenInventory();

	// *Item Get*
	// ??????? 왜 구조체가 포인터 타입으로 전달이 안되는가.. 다른 클래스에서는 됐던 것 같은데 ㅇㅅㅇ... 언리얼 저주...
	// => UFUNCTION()으로 되어 있으면 구조체를 포인터 형식으로 전달 못하나?
	void GetItem(FItemData* ItemData);

private:
	// 아이템 로드
	void LoadArmor();
	




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
