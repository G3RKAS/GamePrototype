// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"

struct FWeaponInfo;

class GAMEPROTOTYPE_API FWeaponTableHelper
{
public:
	static const UDataTable* GetWeaponTable();
	static const FWeaponInfo* GetWeaponInfo(FName InRowName);

	static const FText GetWeaponName(FName InRowName);
	static UStaticMesh* GetWeaponStaticMesh(FName InRowName);
	static const float GetWeaponAttackDamage(FName InRowName);
	static const float GetWeaponAttackSpeed(FName InRowName);

};
