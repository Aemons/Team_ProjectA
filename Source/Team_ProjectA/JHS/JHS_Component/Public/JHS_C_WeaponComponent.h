#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHS_C_WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Katana, Spear, Max//юс╫ц
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM_PROJECTA_API UJHS_C_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetHasWeapon() { return bHasWeapon; }

	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	FORCEINLINE bool IsKatanaMode() { return Type == EWeaponType::Katana; }

public://InputAction Value
	UPROPERTY(EditAnywhere, Category = "Weapon Input")
	class UInputAction* IA_Weapon_Equip;

	UPROPERTY(EditAnywhere, Category = "Weapon Input")
	class UInputAction* IA_Weapon_AttackAction;

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	class UJHS_C_WeaponDataAsset* DataAssets[(int32)EWeaponType::Max];

//Default Function
//////////////////////////////////////////////////////////////////////
public:	
	UJHS_C_WeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	virtual void InitializeComponent() override;
	void SetupInputBinding(class UEnhancedInputComponent* Input);
//////////////////////////////////////////////////////////////////////

public://Weapon Class
	class AJHS_C_Attachment* GetAttachment();
	class UJHS_C_Equipment* GetEquipment();

public://SetMode Function
	void SetUnarmedMode();
	void SetKatanaMode();

	void AttackAction();

	UFUNCTION(BlueprintCallable)
	void SetMode(EWeaponType InType);
private:
	//Current State Check Function
	bool IsIdleMode();
	void ChangeType(EWeaponType InType);

	void PlayerWeaponType();

public://Delegate Value
	FWeaponTypeChanged OnWeaponTypeChanged;

private:
	bool bHasWeapon = false;

	class ACharacter* OwnerCharacter;
	EWeaponType Type = EWeaponType::Max;
};
