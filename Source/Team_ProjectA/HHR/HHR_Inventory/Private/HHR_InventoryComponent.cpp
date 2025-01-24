// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_InventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "JHS_C_Player.h"
#include "Blueprint/UserWidget.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_Inventory.h"

// Sets default values for this component's properties
UHHR_InventoryComponent::UHHR_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UHHR_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
}


// Called every frame
void UHHR_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHHR_InventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();
	

	// Player Character의 InputBinde Delegate에 바인딩
	OwnerCharacter = Cast<AJHS_C_Player>(GetOwner());
	if(OwnerCharacter)
	{
		OwnerCharacter->OnInputBindDelegate.AddUObject(this, &UHHR_InventoryComponent::SetUpInputBinding);
	}
}

void UHHR_InventoryComponent::SetUpInputBinding(UEnhancedInputComponent* Input)
{
	if(Input)
	{
		Input->BindAction(IA_Inventory, ETriggerEvent::Started, this, &UHHR_InventoryComponent::OpenInventory);
	}
}

void UHHR_InventoryComponent::OpenInventory()
{
	if(InventoryWidgetClass)
	{
		// TODO: widget 생성 나중에 ui mananger로 옮겨야 함
		InventoryWidget = CreateWidget<UHHR_Inventory>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		// 임시
		WardrobeActor = GetWorld()->SpawnActor<AActor>(WardrobeTestClass, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
	}
}

