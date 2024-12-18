#include "JHS_C_Anim.h"
#include "JHS_Global.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "JHS_C_Player.h"

void UJHS_C_Anim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<AJHS_C_Player>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
}

void UJHS_C_Anim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	PlayerSpeed();
	PlayerDirection();

	ShouldMove();
	Falling();
}

void UJHS_C_Anim::PlayerSpeed()
{
	Speed = OwnerCharacter->GetVelocity().Size2D();
}

void UJHS_C_Anim::PlayerDirection()
{
	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
	FRotator rotator2 = OwnerCharacter->GetControlRotation();

	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, GetDeltaSeconds(), 25);

	Direction = PrevRotation.Yaw;
}

void UJHS_C_Anim::ShouldMove()
{
	FVector accel = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration();

	if (Speed > 3.0f && accel != FVector::ZeroVector)
		bShouldMove = true;
	else
		bShouldMove = false;
}

void UJHS_C_Anim::Falling()
{
	bIsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
}
