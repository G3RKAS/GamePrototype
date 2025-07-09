// (c) G3RKA. Game Prototype

#include "UI/BaseObjects/WeaponInfoWidget.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "Core/Helpers/WeaponTableHelper.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Components/TextBlock.h"

void UWeaponInfoWidget::SetWeapon(IWeaponInteraction* InWeapon)
{
	WeaponInteraction = InWeapon;
	WeaponInteraction->OnWeaponChanged().AddUObject(this, &ThisClass::ChangeWeaponInformation);
	ChangeWeaponInformation();
}

void UWeaponInfoWidget::SetStats(IStatsInteraction* InStats)
{
	StatsInteraction = InStats;
	ChangeWeaponInformation();
}

void UWeaponInfoWidget::ChangeWeaponInformation()
{
	if (not(WeaponInteraction->GetCurrentWeaponName().IsNone()))
	{
		WeaponInfo->SetText(FWeaponTableHelper::GetWeaponName(WeaponInteraction->GetCurrentWeaponName()));
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
