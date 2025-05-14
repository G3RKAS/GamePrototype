// (c) G3RKA. Game Prototype


#include "Characters/StatsComponent.h"


uint32 UStatsComponent::GetTotalXP()
{
	return XPTotalCount;
}

uint8 UStatsComponent::GetLevel()
{
	return Level;
}

void UStatsComponent::AddXPToTotal(int AddingCount)
{
	SetTotalXP(XPTotalCount + AddingCount);
	UpdateLevel();
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

uint32 UStatsComponent::GetXPForLevel(uint8 LevelToReach)
{
	uint32 TotalXP = 0;
	for (uint8 i{ 1 }; i < LevelToReach; i++)
	{
		TotalXP += XPOnLevelUP * i;
	}

	return TotalXP;
}

uint8 UStatsComponent::GetLevelFromXP(uint32 XpToCount)
{
	uint8 CountedLevel = 0;
	uint32 TotalXP = 0;
	bool bIsCounting = true;
	while (bIsCounting)
	{
		CountedLevel++;
		TotalXP += CountedLevel * XPOnLevelUP;
		if (TotalXP > XpToCount)
		{
			bIsCounting = false;
		}
	}
	return CountedLevel;
}

void UStatsComponent::UpdateLevel()
{
	uint8 NewLevel = GetLevelFromXP(XPTotalCount);
	if (Level < NewLevel)
	{
		Level = NewLevel;
		OnLevelUp.Broadcast(Level);
	}
}

void UStatsComponent::SetTotalXP(uint32 NewTotalXP)
{
	XPTotalCount = FMath::Max(0, (int)NewTotalXP);
}
