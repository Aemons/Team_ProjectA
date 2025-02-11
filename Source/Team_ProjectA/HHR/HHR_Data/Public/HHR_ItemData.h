// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HHR_ItemData.generated.h"

/**
 * 
 */

class UTexture2D;
class USkeletalMesh;

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
	FText ArmorName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EArmorType ArmorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USkeletalMesh* SkeletalMesh;

	FItemData()
		: ItemID(-1) // 기본값 설정
		, ArmorName(FText::FromString(TEXT(""))) // 빈 텍스트 초기화
		, ItemType(EItemType::ArmorItem) // 기본값 (Enum이므로 None 같은 값이 필요)
		, ArmorType(EArmorType::Helmet) // 기본값 (Enum이므로 None 같은 값이 필요)
		, ItemImage(nullptr) // UTexture2D* 초기화
		, SkeletalMesh(nullptr) // USkeletalMesh* 초기화
	{
	}

	FItemData(const FItemData& other)
	{
		ItemID = other.ItemID;
		ArmorName = other.ArmorName;
		ItemType = other.ItemType;
		ArmorType = other.ArmorType;
		ItemImage = other.ItemImage;
		SkeletalMesh = other.SkeletalMesh;
	}

};



class TEAM_PROJECTA_API HHR_ItemData
{
public:
	HHR_ItemData();
	~HHR_ItemData();
};
