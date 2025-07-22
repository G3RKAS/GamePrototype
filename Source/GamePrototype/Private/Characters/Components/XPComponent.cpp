// (c) G3RKA. Game Prototype

#include "Characters/Components/XPComponent.h"

uint32 UXPComponent::GetTotalXP()
{
	return XPTotalCount;
}

float UXPComponent::GetPercentLevel()
{
	uint32 XPPresentLevel = GetXPForLevel(Level);
	return (XPTotalCount - XPPresentLevel) / (GetXPForLevel(Level + 1) - XPPresentLevel);
}

int UXPComponent::GetLevel()
{
	return Level;
}

void UXPComponent::SetLevel(int InLevel)
{
	SetTotalXP(GetXPForLevel(InLevel));
}

FOnLevelUpSignature& UXPComponent::OnLevelUp()
{
	return OnLevelUpEvent;
}

FOnXPUpSignature& UXPComponent::OnXPUp()
{
	return OnXPUpEvent;
}

void UXPComponent::BeginPlay()
{
	Super::BeginPlay();
	XPTotalCount = GetXPForLevel(Level);
}

void UXPComponent::AddXPToTotal(int AddingCount)
{
	SetTotalXP(XPTotalCount + AddingCount);
}

uint32 UXPComponent::GetXPForLevel(uint8 LevelToReach)
{
	uint32 TotalXP = 0;
	for (uint8 i{1}; i < LevelToReach; i++)
	{
		TotalXP += XPOnLevelUP * i;
	}

	return TotalXP;
}

uint8 UXPComponent::GetLevelFromXP(uint32 XpToCount)
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

void UXPComponent::UpdateLevel()
{
	uint8 NewLevel = GetLevelFromXP(XPTotalCount);

	if (Level < NewLevel)
	{
		Level = NewLevel;
		OnLevelUpEvent.Broadcast(Level);	
	}

	OnXPUpEvent.Broadcast();
}

void UXPComponent::SetTotalXP(uint32 NewTotalXP)
{
	XPTotalCount = FMath::Max(0, (int)NewTotalXP);
	UpdateLevel();
}
