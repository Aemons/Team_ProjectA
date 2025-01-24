#include "JHS_C_Player.h"
#include "JHS_Global.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

//Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

//Custom Component
#include "JHS_C_MoveComponent.h"
#include "JHS_C_StateComponent.h"
#include "JHS_C_WeaponComponent.h"

// HHR
// ----------------------------------------------------------------------------
#include "Blueprint/UserWidget.h"
#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractComponent.h"
#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_InventoryComponent.h"
#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractInterface.h"
#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_UIManager.h"
// ----------------------------------------------------------------------------

AJHS_C_Player::AJHS_C_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//CreateComponent
	{
		SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
		CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	}
	
	//Create Actor Component
	{
		MoveComp = CreateDefaultSubobject<UJHS_C_MoveComponent>(TEXT("MoveComp"));
		StateComp = CreateDefaultSubobject<UJHS_C_StateComponent>(TEXT("StateComp"));
		WeaponComp = CreateDefaultSubobject<UJHS_C_WeaponComponent>(TEXT("WeaponComp"));
		// HHR
		// ----------------------------------------------------------------------------
		InteractComp = CreateDefaultSubobject<UHHR_InteractComponent>(TEXT("InteractComp"));
		InventoryComp = CreateDefaultSubobject<UHHR_InventoryComponent>(TEXT("InventoryComp"));
		// ----------------------------------------------------------------------------
	}

	//Attach Component
	{
		SpringArmComp->SetupAttachment(GetMesh());
		CameraComp->SetupAttachment(SpringArmComp);
	}

	//Defatul Setting
	{
		//Mesh Setting
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		bUseControllerRotationYaw = false;
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;

		//SpringArmComp Setting
		SpringArmComp->SetRelativeLocation(FVector(0, 0, 170));
		SpringArmComp->SetRelativeRotation(FRotator(0, 90, 0));
		SpringArmComp->TargetArmLength = 400.0f;
		SpringArmComp->bUsePawnControlRotation = true;
		SpringArmComp->bEnableCameraLag = false;
		SpringArmComp->bDoCollisionTest = false;

		//CameraComp Setting
		CameraComp->bUsePawnControlRotation = false;

		//CharacterMovement Setting
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0, 500.0, 0.0);
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
		GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

		//MaxWalkSpeed Setting
		MoveComp->SetWalk();
	}

	//Default Object Setting
	{
		//InputMappintContext
		{
			static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/00_Project/JHS/JHS_Player/JHS_Input/IMC_Player.IMC_Player'"));
			if (IMC.Succeeded())
				IMC_Player = IMC.Object;
		}

		//InputAction
		{
			static ConstructorHelpers::FObjectFinder<UInputAction> Move(TEXT("/Script/EnhancedInput.InputAction'/Game/00_Project/JHS/JHS_Player/JHS_Input/JHS_InputAction/IA_Player_Move.IA_Player_Move'"));
			if (Move.Succeeded())
				IA_Player_Move = Move.Object;

			static ConstructorHelpers::FObjectFinder<UInputAction> Look(TEXT("/Script/EnhancedInput.InputAction'/Game/00_Project/JHS/JHS_Player/JHS_Input/JHS_InputAction/IA_Player_Look.IA_Player_Look'"));
			if (Look.Succeeded())
				IA_Player_Look = Look.Object;
		}
	}
}

void AJHS_C_Player::BeginPlay()
{
	Super::BeginPlay();
	
	//Player Camera Pitch Degree Limit
	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMin = PitchViewLimit.X;
	GetController<APlayerController>()->PlayerCameraManager->ViewPitchMax = PitchViewLimit.Y;

	// HHR
	// ----------------------------------------------------------------------------
	// *PlayerHUD spawn
	// - UIManager temporary spawn (it will be spawned by GameInstance)
	//UHHR_UIManager* UIManager = NewObject<UHHR_UIManager>();
	//UIManager->Init(GetWorld());
	//UIManager->CreatePlayerHUD();
	// *Temporary
	UUserWidget* playerHUD = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	playerHUD->AddToViewport();
	// ----------------------------------------------------------------------------
	
}

void AJHS_C_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJHS_C_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Player, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Player Move BindAction
		EnhancedInputComp->BindAction(IA_Player_Move, ETriggerEvent::Triggered, this, &AJHS_C_Player::Player_Move);

		//Player Look BindAction
		EnhancedInputComp->BindAction(IA_Player_Look, ETriggerEvent::Triggered, this, &AJHS_C_Player::Player_Look);

		//Player Run BindAction
		EnhancedInputComp->BindAction(IA_Player_Run, ETriggerEvent::Started, this, &AJHS_C_Player::Player_OnRun);
		//Player Move KeyUp BindAction
		EnhancedInputComp->BindAction(IA_Player_Move, ETriggerEvent::Completed, this, &AJHS_C_Player::Player_OffRun);

		//Player Dodge BindAction
		EnhancedInputComp->BindAction(IA_Player_Dodge, ETriggerEvent::Started, this, &AJHS_C_Player::Player_OnDodge);

		//WeaponComponent InputAction Delegate Bind
		if (OnInputBindDelegate.IsBound())
			OnInputBindDelegate.Broadcast(EnhancedInputComp);
	}
}
// HHR
// ----------------------------------------------------------------------------
void AJHS_C_Player::InteractOnMessage(AActor* OtherActor)
{
	if(InteractComp)
	{
		InteractComp->InteractOn(OtherActor);
	}
}

void AJHS_C_Player::InteractOffMessage(AActor* OtherActor)
{
	if(InteractComp)
	{
		InteractComp->InteractOff(OtherActor);
	}
}
// ----------------------------------------------------------------------------

void AJHS_C_Player::Player_Move(const FInputActionValue& InValue)
{
	//CheckTrue(bIsPlayerDodge);

	MovementInput = InValue.Get<FVector2D>();

	const FRotator Rotator = FRotator(0.0, GetControlRotation().Yaw, 0.0);

	const FVector ForwardDirection = FQuat(Rotator).GetForwardVector();
	const FVector RightDirection = FQuat(Rotator).GetRightVector();


	AddMovementInput(ForwardDirection, MovementInput.Y);
	AddMovementInput(RightDirection, MovementInput.X);
}

void AJHS_C_Player::Player_Look(const FInputActionValue& InValue)
{
	LookInput = InValue.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void AJHS_C_Player::Player_OnRun()
{
	//Toggle Input
	bIsPlayerRun = !bIsPlayerRun;

	if (WeaponComp->GetHasWeapon() == false)
	{
		if (GetVelocity().Size2D() > 100.0f && bIsPlayerRun == true)
		{
			MoveComp->SetJog();
		}

		if (GetVelocity().Size2D() > 100.0f && bIsPlayerRun == false)
		{
			MoveComp->SetWalk();
		}
	}
	else if (WeaponComp->GetHasWeapon() == true)
	{
		if (GetVelocity().Size2D() > 100.0f && bIsPlayerRun == true)
		{
			MoveComp->SetSprint();
		}

		if (GetVelocity().Size2D() > 100.0f && bIsPlayerRun == false)
		{
			MoveComp->SetJog();
		}
	}
}

void AJHS_C_Player::Player_OffRun()
{
	PlayerBrakingWalkingValue();

	if (WeaponComp->GetHasWeapon() == false)
		MoveComp->SetWalk();
	
	if (WeaponComp->GetHasWeapon() == true)
		MoveComp->SetJog();

	bIsPlayerRun = false;

	GetWorld()->GetTimerManager().SetTimer(BrakingWalkingHandle, this, &AJHS_C_Player::PlayerBrakingWalkingValue, 0.8f, false);
}

void AJHS_C_Player::Player_OnDodge()
{ 
	if (WeaponComp->GetHasWeapon() == true && GetVelocity().Length() > 5.0f && StateComp->IsActionMode() == false && bIsPlayerDodge == false)
	{
		StopAnimMontage();
		
		bIsPlayerDodge = true;
	
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		
		//Dodge Direction
		///////////////////////////////////////////////////////////////
		FVector InputVector = GetLastMovementInputVector();

		//�Է��� ������� �⺻ Dodge ������ �� �������� 
		if (InputVector.IsNearlyZero())
			InputVector = GetActorForwardVector() * -1.0f;
		
		FVector DodgeDirection = InputVector.GetSafeNormal();

		if (DodgeDirection.IsNearlyZero())
			return;

		UAnimMontage* DodgeMontage = nullptr;

		float ForwardDot = FVector::DotProduct(GetActorForwardVector(), DodgeDirection);
		float RightDot = FVector::DotProduct(GetActorRightVector(), DodgeDirection);

		if (ForwardDot > 0.7f)
		{
			//Forward Dodge
			DodgeMontage = DodgeMontages[0];
		}
		else if (ForwardDot < -0.7f)
		{
			//Backward Dodge
			DodgeMontage = DodgeMontages[1];
		}
		else if (RightDot > 0.7f)
		{
			//Right Dodge
			DodgeMontage = DodgeMontages[2];
		}
		else if (RightDot < -0.7f)
		{
			//Left Dodge
			DodgeMontage = DodgeMontages[3];
		}

		if (DodgeMontage)
			PlayAnimMontage(DodgeMontage, DodgeMontage_PlayRate);

		DisableInput(Cast<APlayerController>(GetController()));
		///////////////////////////////////////////////////////////////

		GetWorld()->GetTimerManager().SetTimer(OffDodgeHandle, this, &AJHS_C_Player::Player_OffDodge, DodgeDelay, false);
	}
}

void AJHS_C_Player::Player_OffDodge()
{
	if (WeaponComp->GetHasWeapon() == true && StateComp->IsActionMode() == false)
	{
		bIsPlayerDodge = false;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);

		EnableInput(Cast<APlayerController>(GetController()));
	}
}

void AJHS_C_Player::PlayerBrakingWalkingValue()
{
	//Player Running
	if (bIsPlayerRun == true)
	{
		GetCharacterMovement()->BrakingDecelerationWalking = 200.0f;
		GetCharacterMovement()->GroundFriction = 2.0f;
	}

	//Player Walking
	if (bIsPlayerRun == false)
	{
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
		GetCharacterMovement()->GroundFriction = 8.0f;
	}
}
