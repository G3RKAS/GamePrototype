// (c) G3RKA. Game Prototype

#include "Core/Helpers/WeaponTableHelper.h"
#include <Core/GameDeveloperSettings.h>
#include <Core/Helpers/DataTableHelper.h>
#include <Core/GameBaseTypes.h>

const bool FWeaponTableHelper::HasWeaponInTable(FName InRowName)
{
	return GetWeaponTable()->GetRowNames().Contains(InRowName);
}

const FText FWeaponTableHelper::GetWeaponName(FName InRowName)
{
	const FWeaponInfo* WeaponInfo = GetWeaponInfo(InRowName);
	check(WeaponInfo);
	return WeaponInfo->WeaponName;
}

UStaticMesh* FWeaponTableHelper::GetWeaponStaticMesh(FName InRowName)
{
	const FWeaponInfo* WeaponInfo = GetWeaponInfo(InRowName);
	check(WeaponInfo);
	return WeaponInfo->WeaponStaticMesh.LoadSynchronous();
}

const float FWeaponTableHelper::GetWeaponAttackDamage(FName InRowName)
{
	const FWeaponInfo* WeaponInfo = GetWeaponInfo(InRowName);
	check(WeaponInfo);
	return WeaponInfo->WeaponAttackDamage;
}

const float FWeaponTableHelper::GetWeaponAttackSpeed(FName InRowName)
{
	const FWeaponInfo* WeaponInfo = GetWeaponInfo(InRowName);
	check(WeaponInfo);
	return WeaponInfo->WeaponAttackSpeed;
}

const FWeaponInfo* FWeaponTableHelper::GetWeaponInfo(FName InRowName)
{
	return FDataTableHelper::FindRow<FWeaponInfo>(GetWeaponTable(), InRowName);
}

const UDataTable* FWeaponTableHelper::GetWeaponTable()
{
	const UGameDeveloperSettings* GameSettings = GetDefault<UGameDeveloperSettings>();
	check(GameSettings);
	return GameSettings->WeaponData.LoadSynchronous();
}
