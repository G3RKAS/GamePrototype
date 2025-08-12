// (c) G3RKA. Game Prototype

#include "Characters/Components/StatsLevelingComponent.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"

void UStatsLevelingComponent::BeginPlay()
{
	Super::BeginPlay();
	StatsInteraction = Cast<IStatsInteraction>(GetOwner());
	LevelInteraction = GetOwner()->FindComponentByInterface<ILevelInteraction>();
	WeaponInteraction = GetOwner()->FindComponentByInterface<IWeaponInteraction>();

	SetupStats();
	if (LevelInteraction)
	{
		LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::CalculateNewStats);
	}
	if (WeaponInteraction)
	{
		WeaponInteraction->OnWeaponChanged().AddUObject(this, &ThisClass::HandleWeaponChange);
	}
}

float UStatsLevelingComponent::GetLevelStat(float Stat)
{
	if (StatsInteraction)
	{
		return Stat * pow(1.1, LevelInteraction->GetLevel() - 1);
	}
	return -1;
}

void UStatsLevelingComponent::SetupStats()
{
	if (StatsInteraction)
	{
		BaseMaxHealth = StatsInteraction->GetMaxHealth();

		float CurrentMaxHealth = GetLevelStat(BaseMaxHealth);
		
		StatsInteraction->SetMaxHealth(CurrentMaxHealth);
		StatsInteraction->SetCurrentHealth(CurrentMaxHealth);

		SetupWeaponStats();
	}
}

void UStatsLevelingComponent::SetupWeaponStats()
{
	if (StatsInteraction)
	{
		BaseAttackDamage = StatsInteraction->GetAttackDamage();
		BaseAttackSpeed = StatsInteraction->GetAttackSpeed();

		StatsInteraction->SetAttackDamage(GetLevelStat(BaseAttackDamage));
		StatsInteraction->SetAttackSpeed(GetLevelStat(BaseAttackSpeed));
	}
}

void UStatsLevelingComponent::HandleWeaponChange(FName InWeaponName)
{
	SetupWeaponStats();
}

void UStatsLevelingComponent::CalculateNewStats(uint8)
{
	if (StatsInteraction)
	{
		StatsInteraction->SetMaxHealth(GetLevelStat(BaseMaxHealth));
		StatsInteraction->SetAttackDamage(GetLevelStat(BaseAttackDamage));
		StatsInteraction->SetAttackSpeed(GetLevelStat(BaseAttackSpeed));

		UE_LOG(LogTemp, Warning, TEXT("Name = %s Level = %d MaxHealth = %f AttackDamage = %f AttackSpeed = %f"),
			   *GetOwner()->GetName(), LevelInteraction->GetLevel(), StatsInteraction->GetMaxHealth(),
			   StatsInteraction->GetAttackDamage(), StatsInteraction->GetAttackSpeed())
	}
}
