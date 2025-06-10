// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/DataTable.h"
#include "GameDeveloperSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Game Settings"))
class GAMEPROTOTYPE_API UGameDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditDefaultsOnly, Category = "DataTables")
	TSoftObjectPtr<UDataTable> WeaponData;
};
