// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "World/Weapon/GameBaseWeapon.h"
#include "GameAttackWeapon.generated.h"

UCLASS()
class GAMEPROTOTYPE_API AGameAttackWeapon : public AGameBaseWeapon
{
	GENERATED_BODY()

public:
	AGameAttackWeapon();

	float GetAttackDamage();
	float GetAttackSpeed();
	void SetAttackDamage(float);
	void SetAttackSpeed(float);

	virtual void ChangeWeaponBasedOnName(FName) override;

private:
	float WeaponAttackDamage = 0.f;

	float WeaponAttackSpeed = 0.f;

	void SetupWeaponStats();
};
