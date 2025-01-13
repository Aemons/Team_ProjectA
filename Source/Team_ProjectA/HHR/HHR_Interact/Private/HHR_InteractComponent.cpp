// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractComponent.h"

#include "EnhancedInputComponent.h"
#include "JHS_C_Player.h"


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
	UE_LOG(LogTemp, Warning, TEXT("시벌 뭐야"));
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

	// Player Character의 InputBinde Delegate에 바인딩
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Init");
	UE_LOG(LogTemp, Warning, TEXT("HHR_InteractComponent initialized"));
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "F");
	// TODO : LineTrace로 Interact 구현 
}



