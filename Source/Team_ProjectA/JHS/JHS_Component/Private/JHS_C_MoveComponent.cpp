#include "JHS_C_MoveComponent.h"
#include "JHS_Global.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "JHS_C_Player.h"

UJHS_C_MoveComponent::UJHS_C_MoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UJHS_C_MoveComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UJHS_C_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJHS_C_MoveComponent::SetWalk()
{
	SetWalkSpeed(EWalkSpeedType::Walk);
}

void UJHS_C_MoveComponent::SetJog()
{
	SetWalkSpeed(EWalkSpeedType::Jog);
}

void UJHS_C_MoveComponent::SetSprint()
{
	SetWalkSpeed(EWalkSpeedType::Sprint);
}

void UJHS_C_MoveComponent::SetWalkSpeed(EWalkSpeedType InType)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerSpeed[(int32)InType];

	CurrentPlayerSpeed = PlayerSpeed[(int32)InType];
}

void UJHS_C_MoveComponent::SearchEnemyTarget()
{
	//근처에 Enemy가 있을 경우
	if (true)
	{

	}
	else //근처에 Enemy가 없을 경우
	{

	}
}

void UJHS_C_MoveComponent::EnableControlRotation()
{
	bIsControlRotation = true;

	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UJHS_C_MoveComponent::DisableControlRotation()
{
	bIsControlRotation = false;

	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

