// (c) G3RKA. Game Prototype

#include "UI/BaseObjects/WeaponInfoWidget.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "Core/Helpers/WeaponTableHelper.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Components/TextBlock.h"

void UWeaponInfoWidget::SetLevel(ILevelInteraction* InLevel)
{
	LevelInteraction = InLevel;
	LevelInteraction->OnXPUp().AddUObject(this, &ThisClass::LevelHandler);
	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::InitChangeWeaponInformation);
}

void UWeaponInfoWidget::SetWeapon(IWeaponInteraction* InWeapon)
{
	WeaponInteraction = InWeapon;
	WeaponInteraction->OnWeaponChanged().AddUObject(this, &ThisClass::ChangeWeaponInformation);
	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::InitChangeWeaponInformation);
}

void UWeaponInfoWidget::SetStats(IStatsInteraction* InStats)
{
	StatsInteraction = InStats;
	InitChangeWeaponInformation();
}

void UWeaponInfoWidget::LevelHandler()
{
	InitChangeWeaponInformation();
}

void UWeaponInfoWidget::InitChangeWeaponInformation()
{
	ChangeWeaponInformation(WeaponInteraction->GetCurrentWeaponName());
}

void UWeaponInfoWidget::ChangeWeaponInformation(FName InWeaponName)
{
	if (not(InWeaponName.IsNone()))
	{
		WeaponInfo->SetText(FWeaponTableHelper::GetWeaponName(InWeaponName));
		if (StatsInteraction)
		{
			DamageInfo->SetText(FText::AsNumber(StatsInteraction->GetAttackDamage()));
		}
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
