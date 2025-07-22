// (c) G3RKA. Game Prototype

#include "World/Weapon/GameAttackWeapon.h"
#include <Core/Helpers/WeaponTableHelper.h>

AGameAttackWeapon::AGameAttackWeapon() : Super()
{
	SetActorEnableCollision(false);
}

float AGameAttackWeapon::GetAttackDamage()
{
	return WeaponAttackDamage;
}

float AGameAttackWeapon::GetAttackSpeed()
{
	return WeaponAttackSpeed;
}

void AGameAttackWeapon::SetAttackDamage(float InAttackDamage)
{
	WeaponAttackDamage = InAttackDamage;
}

void AGameAttackWeapon::SetAttackSpeed(float InAttackSpeed)
{
	WeaponAttackSpeed = InAttackSpeed;
}

void AGameAttackWeapon::ChangeWeaponBasedOnName(FName InWeaponRowName)
{
	Super::ChangeWeaponBasedOnName(InWeaponRowName);
	SetupWeaponStats();
}

void AGameAttackWeapon::SetupWeaponStats()
{
	WeaponAttackDamage = FWeaponTableHelper::GetWeaponAttackDamage(WeaponRow.RowName);
	WeaponAttackSpeed = FWeaponTableHelper::GetWeaponAttackSpeed(WeaponRow.RowName);
}