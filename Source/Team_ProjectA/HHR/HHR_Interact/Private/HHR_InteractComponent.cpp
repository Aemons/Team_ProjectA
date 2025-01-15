// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractComponent.h"

#include "EnhancedInputComponent.h"
#include "JHS_C_Player.h"
#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractInterface.h"


// Sets default values for this component's properties
UHHR_InteractComponent::UHHR_InteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UHHR_InteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UHHR_InteractComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// BeginPlay() 실행하기 전에 실행 
void UHHR_InteractComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// TODO : 실제 IMC와 Playercharacter에 할당해줘야함 (playerCharacter에서 interactcomp생성)
	// Player Character의 InputBinde Delegate에 바인딩
	OwnerCharacter = Cast<AJHS_C_Player>(GetOwner());
	if(OwnerCharacter)
	{
		OwnerCharacter->OnInputBindDelegate.AddUObject(this, &UHHR_InteractComponent::SetUpInputBinding);
	}
}

void UHHR_InteractComponent::SetUpInputBinding(UEnhancedInputComponent* Input)
{
	if(Input)
	{
		Input->BindAction(IA_Interact, ETriggerEvent::Started, this, &UHHR_InteractComponent::Interact);
	}
}

void UHHR_InteractComponent::Interact()
{
	// F 키 누르면 실행
	if(InteractActor)
	{
		// Interact 함수 호출
		IHHR_InteractInterface* interface = Cast<IHHR_InteractInterface>(InteractActor);
		interface->Interact();
		// view 조정... npc에서 해줘야 하나, comp에서 해줘야 하나 
		APlayerController* pc = Cast<APlayerController>(OwnerCharacter->GetController());
		pc->SetViewTarget(InteractActor);
	}
}

void UHHR_InteractComponent::InteractOn(AActor* OtherActor)
{
	if(OtherActor->Implements<UHHR_InteractInterface>())
	{
		InteractActor = OtherActor;
	}
}

void UHHR_InteractComponent::InteractOff(AActor* OtherActor)
{
	if(OtherActor->Implements<UHHR_InteractInterface>())
	{
		InteractActor = nullptr;
	}
}



