#include "JHS_C_Player.h"
#include "JHS_Global.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


AJHS_C_Player::AJHS_C_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//CreateComponent
	{
		SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
		CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	}
	
	//Attach Component
	{
		SpringArmComp->SetupAttachment(GetMesh());
		CameraComp->SetupAttachment(SpringArmComp);
	}

	//Defatul Setting
	{
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		bUseControllerRotationYaw = false;
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;

		SpringArmComp->SetRelativeLocation(FVector(0, 0, 170));
		SpringArmComp->SetRelativeRotation(FRotator(0, 90, 0));
		SpringArmComp->TargetArmLength = 400.0f;
		SpringArmComp->bUsePawnControlRotation = true;
		SpringArmComp->bEnableCameraLag = false;
		SpringArmComp->bDoCollisionTest = false;

		CameraComp->bUsePawnControlRotation = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0, 500.0, 0.0);
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
		GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
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
	}
}

void AJHS_C_Player::Player_Move(const FInputActionValue& InValue)
{
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

void AJHS_C_Player::Player_Run()
{


}