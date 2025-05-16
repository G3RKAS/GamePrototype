// (c) G3RKA. Game Prototype


#include "Characters/StatsLevelingComponent.h"

void UStatsLevelingComponent::BeginPlay()
{
	Super::BeginPlay();
	StatsInteraction = Cast<IStatsInteraction>(GetOwner());
	LevelInteraction = Cast<ILevelInteraction>(GetOwner());

	SetupStats();
	if (LevelInteraction)
	{
		LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::CalculateNewStats);
	}
}

float UStatsLevelingComponent::GetLevelStat(float Stat)
{
	if (StatsInteraction)
	{
		return Stat * pow(1.1, LevelInteraction->GetLevel());
	}
	return -1;
}

void UStatsLevelingComponent::SetupStats()
{
	if (StatsInteraction)
	{
		BaseMaxHealth = StatsInteraction->GetMaxHealth();

		StatsInteraction->SetMaxHealth(GetLevelStat(BaseMaxHealth));

		EquipWeapon();
	}
}

void UStatsLevelingComponent::EquipWeapon()
{
	if (StatsInteraction)
	{
		BaseAttackDamage = StatsInteraction->GetAttackDamage();
		BaseAttackSpeed = StatsInteraction->GetAttackSpeed();

		StatsInteraction->SetAttackDamage(GetLevelStat(BaseAttackDamage));
		StatsInteraction->SetAttackSpeed(GetLevelStat(BaseAttackSpeed));
	}
}

void UStatsLevelingComponent::CalculateNewStats(uint8)
{
	if (StatsInteraction)
	{
		StatsInteraction->SetMaxHealth(GetLevelStat(BaseMaxHealth));
		StatsInteraction->SetAttackDamage(GetLevelStat(BaseAttackDamage));
		StatsInteraction->SetAttackSpeed(GetLevelStat(BaseAttackSpeed));
	}
}
