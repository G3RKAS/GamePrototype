// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameBaseTypes.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText WeaponName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UStaticMesh> WeaponStaticMesh;

	UPROPERTY(EditDefaultsOnly)
	float WeaponAttackDamage;

	UPROPERTY(EditDefaultsOnly)
	float WeaponAttackSpeed;

};