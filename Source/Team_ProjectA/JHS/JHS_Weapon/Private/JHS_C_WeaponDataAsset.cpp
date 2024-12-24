#include "JHS_C_WeaponDataAsset.h"
#include "JHS_Global.h"

#include "GameFramework/Character.h"

//Weapon Class
#include "JHS_C_Attachment.h"
#include "JHS_C_Equipment.h"


UJHS_C_WeaponDataAsset::UJHS_C_WeaponDataAsset()
{
	AttachmentClass = AJHS_C_Attachment::StaticClass();
	EquipmentClass = UJHS_C_Equipment::StaticClass();
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
}
