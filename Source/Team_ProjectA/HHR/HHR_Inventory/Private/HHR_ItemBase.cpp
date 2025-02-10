// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_ItemBase.h"

#include "JHS_C_Player.h"
#include "Components/SphereComponent.h"
#include "Team_ProjectA/HHR/HHR_Inventory/Public/HHR_InventoryComponent.h"


// Sets default values
AHHR_ItemBase::AHHR_ItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component 생성
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Comp"));
	SetRootComponent(SphereCollision);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SphereCollision);

	
}

// Called when the game starts or when spawned
void AHHR_ItemBase::BeginPlay()
{
	Super::BeginPlay();

	// 바인딩
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AHHR_ItemBase::OnComponentBeginOverlap);

	// Color Setting
	SetColor();
}

// Called every frame
void AHHR_ItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AHHR_ItemBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// PlayerCharacter이면 Inventory Comp에게 ItemData 넘겨주기 + 자기 자신 삭제
	// TODO:  delegate로 처리하는 거에 대해서 고려
	// TODO : 아이템 얻었을 때 sound
	AJHS_C_Player* player = Cast<AJHS_C_Player>(OtherActor);
	if(player)
	{
		UHHR_InventoryComponent* inventory = player->GetInventoryComp();
		if(inventory)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Collision!");

			inventory->GetItem(&ItemData);
		}

		Destroy();
	}




	
}

void AHHR_ItemBase::SetColor()
{
	
	if(!StaticMeshComp || ItemColors.Num() < 4) return;
	
	switch(ItemData.ArmorType)
	{
	case EArmorType::Helmet:
		StaticMeshComp->SetMaterial(0, ItemColors[0]);
		break;
	case EArmorType::Chest:
		StaticMeshComp->SetMaterial(0, ItemColors[1]);
		break;
	case EArmorType::Pants:
		StaticMeshComp->SetMaterial(0, ItemColors[2]);
		break;
	case EArmorType::Boots:
		StaticMeshComp->SetMaterial(0, ItemColors[3]);
		break;
	default:
		break;
	}
}



