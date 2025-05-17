// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "StatsLevelingComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UStatsLevelingComponent : public UActorComponent
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

	float BaseMaxHealth;
	float BaseAttackDamage;
	float BaseAttackSpeed;
};

