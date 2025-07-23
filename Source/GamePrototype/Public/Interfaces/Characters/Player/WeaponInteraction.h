// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponChangedSignature)
DECLARE_MULTICAST_DELEGATE(FOnAnimNotifySignature)

class AGameBaseWeapon;

UINTERFACE(MinimalAPI)
class UWeaponInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IWeaponInteraction
{
	GENERATED_BODY()
public:
	virtual void EquipWeapon(FName) = 0;
	virtual FName GetCurrentWeaponName() = 0;
	virtual FOnWeaponChangedSignature& OnWeaponChanged() = 0;
	virtual FOnAnimNotifySignature& OnWeaponAttackStart() = 0;
	virtual FOnAnimNotifySignature& OnWeaponAttackEnd() = 0;
};
