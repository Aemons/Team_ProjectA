// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_InventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "JHS_C_Player.h"
#include "Blueprint/UserWidget.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Team_ProjectA/HHR/HHR_Data/Public/HHR_ItemData.h"
#include "Team_ProjectA/HHR/HHR_Game/Public/HHR_GameInstance.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_Inventory.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/UIComponents/HHR_ItemSlotTest.h"

// Sets default values for this component's properties
UHHR_InventoryComponent::UHHR_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// InitializeComponent() 함수 사용하기 위해 필요 
	bWantsInitializeComponent = true;

	/*SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("InventoryComp Component");
	if(GetOwner())
	{
		SpringArmComp->SetupAttachment(GetOwner()->GetRootComponent());
	}
	CaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>("InventoryComp capture Component");
	if(GetOwner())
	{
		CaptureComp->SetupAttachment(SpringArmComp);
	}*/
}


// Called when the game starts
void UHHR_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadArmor();

	// ...
	if(Wardrobe)
	{
		CaptureComp->TextureTarget = Wardrobe;
		CaptureComp->CaptureScene();
	}


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

	// Scene Component 생성 후 OwnerCharacter에 부착
	SpringArmComp = NewObject<USpringArmComponent>(OwnerCharacter);
	if(SpringArmComp)
	{
		SpringArmComp->RegisterComponent();
		SpringArmComp->AttachToComponent(OwnerCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		// 블루프린트에 등록
		OwnerCharacter->AddInstanceComponent(SpringArmComp);
		/*SpringArmComp->Modify();
		OwnerCharacter->MarkPackageDirty();*/
	}
	CaptureComp = NewObject<USceneCaptureComponent2D>(OwnerCharacter);
	if(CaptureComp)
	{
		CaptureComp->RegisterComponent();
		CaptureComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
		// 블루프린트에 등록
		OwnerCharacter->AddInstanceComponent(CaptureComp);
	}
	
	// Setting
	if(SpringArmComp && CaptureComp)
	{
		// Sprint Arm Compㅈㅈ
		SpringArmComp->SetRelativeRotation(FRotator(-10, 180, 0));
		SpringArmComp->SetRelativeLocation(FVector(0, 0, 50));
		SpringArmComp->TargetArmLength = 250;

		// Scene Capture Comp
		CaptureComp->ShowOnlyActorComponents(OwnerCharacter);
		CaptureComp->FOVAngle = 65.f;
	}

	
}

void UHHR_InventoryComponent::ChangeArmor(UHHR_ItemSlotTest* Armor)
{

	// 옷 바꿀때 Item도 같이 넣어줌
	UHHR_GameInstance* GI = Cast<UHHR_GameInstance>(GetWorld()->GetGameInstance());
	if(!GI) return;
	
	switch (Armor->ItemData.ArmorType)
	{
	case EArmorType::Helmet:
		OwnerCharacter->GetHelmetSMComp()->SetSkeletalMesh(Armor->ItemData.SkeletalMesh);
		InventoryWidget->ChangeHelemtSlot(&Armor->ItemData);
		GI->SetEqHelmetData(&Armor->ItemData);
		break;
	case EArmorType::Chest:
		OwnerCharacter->GetChestSMComp()->SetSkeletalMesh(Armor->ItemData.SkeletalMesh);
		InventoryWidget->ChangeChestSlot(&Armor->ItemData);
		GI->SetEqChestData(&Armor->ItemData);
		break;
	case EArmorType::Pants:
		OwnerCharacter->GetPantsSMComp()->SetSkeletalMesh(Armor->ItemData.SkeletalMesh);
		InventoryWidget->ChangePantsSlot(&Armor->ItemData);
		GI->SetEqPantsData(&Armor->ItemData);
		break;
	case EArmorType::Boots:
		OwnerCharacter->GetBootsSMComp()->SetSkeletalMesh(Armor->ItemData.SkeletalMesh);
		InventoryWidget->ChangeBootsSlot(&Armor->ItemData);
		GI->SetEqBootsData(&Armor->ItemData);
		break;
	default:
		break;
	}
	
}

void UHHR_InventoryComponent::CloseInventory()
{
	// 닫기
	bIsOpen = false;
	InventoryWidget->RemoveFromParent();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->bShowMouseCursor = false;
	PC->SetIgnoreLookInput(false);
	PC->SetIgnoreMoveInput(false);

	FInputModeGameOnly InputMode;
	PC->SetInputMode(InputMode);
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
	if(InventoryWidgetClass && !bIsOpen)
	{
		bIsOpen = true;
		// TODO: widget 생성 나중에 ui mananger로 옮겨야 함
		InventoryWidget = CreateWidget<UHHR_Inventory>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		// Delegate 바인드
		if(InventoryWidget)
		{
			InventoryWidget->OnInventoryClose.BindUObject(this, &UHHR_InventoryComponent::CloseInventory);
		}
		
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PC->bShowMouseCursor = true;
		PC->SetIgnoreLookInput(true);
		PC->SetIgnoreMoveInput(true);

		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}
	else
	{
		// 닫기
		bIsOpen = false;
		InventoryWidget->RemoveFromParent();

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PC->bShowMouseCursor = false;
		PC->SetIgnoreLookInput(false);
		PC->SetIgnoreMoveInput(false);

		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

	}
}

void UHHR_InventoryComponent::LoadArmor()
{

	UHHR_GameInstance* GI = Cast<UHHR_GameInstance>(GetWorld()->GetGameInstance());
	if(GI)
	{
		OwnerCharacter->GetHelmetSMComp()->SetSkeletalMesh(GI->GetEqHelmetData()->SkeletalMesh);
		OwnerCharacter->GetChestSMComp()->SetSkeletalMesh(GI->GetEqChestData()->SkeletalMesh);
		OwnerCharacter->GetPantsSMComp()->SetSkeletalMesh(GI->GetEqPantsData()->SkeletalMesh);
		OwnerCharacter->GetBootsSMComp()->SetSkeletalMesh(GI->GetEqBootsData()->SkeletalMesh);
	}
	
}












