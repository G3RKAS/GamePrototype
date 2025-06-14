// (c) G3RKA. Game Prototype

#include "Core/Helpers/WeaponTableHelper.h"
#include <Core/GameDeveloperSettings.h>

const UDataTable* WeaponTableHelper::GetWeaponTable()
{
	const UGameDeveloperSettings* GameSettings = GetDefault<UGameDeveloperSettings>();
	check(GameSettings);
	return GameSettings->WeaponData.LoadSynchronous();
}
