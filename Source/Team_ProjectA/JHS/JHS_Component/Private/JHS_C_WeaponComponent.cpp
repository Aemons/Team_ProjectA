#include "JHS_C_WeaponComponent.h"
#include "JHS_Global.h"

#include "EnhancedInputComponent.h"

#include "JHS_C_StateComponent.h"

#include "JHS_C_WeaponDataAsset.h"

#include "JHS_C_Player.h"

UJHS_C_WeaponComponent::UJHS_C_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UJHS_C_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(OwnerCharacter);
	}

	PlayerWeaponType();
}

void UJHS_C_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UJHS_C_WeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	if (AJHS_C_Player* Player = Cast<AJHS_C_Player>(OwnerCharacter))
	{
		Player->OnInputBindDelegate.AddUObject(this, &UJHS_C_WeaponComponent::SetupInputBinding);
	}
}

void UJHS_C_WeaponComponent::SetupInputBinding(UEnhancedInputComponent* Input)
{
	if (!!Input)
	{
		//Weapon Attack Input
		Input->BindAction(IA_Weapon_AttackAction, ETriggerEvent::Started, this, &UJHS_C_WeaponComponent::AttackAction);
	}
}

AJHS_C_Attachment* UJHS_C_WeaponComponent::GetAttachment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);

	return DataAssets[(int32)Type]->GetAttachment();
}

void UJHS_C_WeaponComponent::SetUnamredMode()
{
	SetMode(EWeaponType::Max);
}

void UJHS_C_WeaponComponent::SetKatanaMode()
{
	SetMode(EWeaponType::Katana);
}

void UJHS_C_WeaponComponent::AttackAction()
{

}

bool UJHS_C_WeaponComponent::IsIdleMode()
{
	return Cast<UJHS_C_StateComponent>(OwnerCharacter->GetComponentByClass(UJHS_C_StateComponent::StaticClass()))->IsIdleMode();
}

void UJHS_C_WeaponComponent::SetMode(EWeaponType InType)
{
	if (!!DataAssets[(int32)InType])
	{
		//DataAssets[(int32)InType]->GetEquipment()->Equip();
		ChangeType(InType);

		bHasWeapon = true;
	}
}

void UJHS_C_WeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType PrevType = Type;
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(PrevType, Type);
}

void UJHS_C_WeaponComponent::PlayerWeaponType()
{
	if (AJHS_C_Player* Player = Cast<AJHS_C_Player>(OwnerCharacter))
	{
		Type = Player->GetPlayerWeaponType();
	}
}

