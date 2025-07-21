// (c) G3RKA. Game Prototype


#include "World/Weapon/GameAttackWeapon.h"

float AGameAttackWeapon::GetAttackDamage()
{
	return WeaponAttackDamage;
}

float AGameAttackWeapon::GetAttackSpeed()
{
	return WeaponAttackSpeed;
}

void AGameAttackWeapon::ChangeWeaponBasedOnName(FName InWeaponRowName)
{
	Super::ChangeWeaponBasedOnName(InWeaponRowName);
	SetupWeaponStats();
}

void AGameAttackWeapon::SetupWeaponStats()
{
	WeaponAttackDamage = 0.f;
	WeaponAttackSpeed = 0.f;
}