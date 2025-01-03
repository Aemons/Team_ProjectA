#include "JHS_C_WeaponDataAsset.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

//Weapon Class
#include "JHS_C_Attachment.h"
#include "JHS_C_Equipment.h"
#include "JHS_C_MainAction.h"

UJHS_C_WeaponDataAsset::UJHS_C_WeaponDataAsset()
{
	AttachmentClass = AJHS_C_Attachment::StaticClass();
	EquipmentClass = UJHS_C_Equipment::StaticClass();
	MainActionClass = UJHS_C_MainAction::StaticClass();
}

void UJHS_C_WeaponDataAsset::BeginPlay(ACharacter* InOwner)
{
	if (!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		Attachment = InOwner->GetWorld()->SpawnActor<AJHS_C_Attachment>(AttachmentClass, params);
	}

	if (!!EquipmentClass)
	{
		Equipment = NewObject<UJHS_C_Equipment>(this, EquipmentClass);
		Equipment->BeginPlay(InOwner, EquipmentData);

		if (!!Attachment)
		{
			Equipment->OnEquipmentBeginEquip.AddDynamic(Attachment, &AJHS_C_Attachment::OnBeginEquip);
			Equipment->OnEquipmentEndEquip.AddDynamic(Attachment, &AJHS_C_Attachment::OnEndEquip);
			Equipment->OnEquipmentUnequip.AddDynamic(Attachment, &AJHS_C_Attachment::OnUnequip);
		}
	}

	if (!!MainActionClass)
	{
		MainAction = NewObject<UJHS_C_MainAction>(this, MainActionClass);
		MainAction->BeginPlay(Attachment, Equipment, InOwner, MainActionData);

		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginCollision.AddDynamic(MainAction, &UJHS_C_MainAction::OnAttachmentBeginCollision);
			Attachment->OnAttachmentEndCollision.AddDynamic(MainAction, &UJHS_C_MainAction::OnAttachmentEndCollision);

			Attachment->OnAttachmentBeginOverlap.AddDynamic(MainAction, &UJHS_C_MainAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(MainAction, &UJHS_C_MainAction::OnAttachmentEndOverlap);
		}

		if (!!Equipment)
		{
			Equipment->OnEquipmentBeginEquip.AddDynamic(MainAction, &UJHS_C_MainAction::OnBegin_Equip);
			Equipment->OnEquipmentEndEquip.AddDynamic(MainAction, &UJHS_C_MainAction::OnUnequip);
		}
	}
}
