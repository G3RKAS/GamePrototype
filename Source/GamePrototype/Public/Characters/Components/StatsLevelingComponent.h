// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "StatsLevelingComponent.generated.h"

class IStatsInteraction;
class ILevelInteraction;
class IWeaponInteraction;

UCLASS()
class GAMEPROTOTYPE_API UStatsLevelingComponent : public UBaseActorComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void SetupWeaponStats();

private:
	float GetLevelStat(float);
	void SetupStats();
	void CalculateNewStats(uint8);

	IStatsInteraction* StatsInteraction;
	ILevelInteraction* LevelInteraction;
	IWeaponInteraction* WeaponInteraction;

	float BaseMaxHealth;
	float BaseAttackDamage;
	float BaseAttackSpeed;
};

