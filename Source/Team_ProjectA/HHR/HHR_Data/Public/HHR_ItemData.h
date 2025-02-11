// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HHR_ItemData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	Helmet,
	Chest,
	Pants,
	Hands,
	Boots
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ArmorItem,
	ConsumableItem
};

// 아이템 구조체
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EArmorType ArmorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class USkeletalMesh* SkeletalMesh;

};



class TEAM_PROJECTA_API HHR_ItemData
{
public:
	HHR_ItemData();
	~HHR_ItemData();
};
