// (c) G3RKA. Game Prototype


#include "UI/HUDWidget/GameHUDWidget.h"
#include "UI/BaseObjects/GamePlayerHealthBar.h"

#include "UI/BaseObjects/WeaponInfoWidget.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "Interfaces/Characters/StatsInteraction.h"

#include "UI/BaseObjects/Messages/GameMessageBoxWidget.h"

void UGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (HealthBar)
	{
		HealthBar->SetBindType(EBindType::Owner);
	}
	if (WeaponInfo)
	{
		IWeaponInteraction* WeaponInteraction = GetOwningPlayerPawn()->FindComponentByInterface<IWeaponInteraction>();

		if (WeaponInteraction)
		{
			WeaponInfo->SetWeapon(WeaponInteraction);
		}

		IStatsInteraction* StatsInteraction = Cast<IStatsInteraction>(GetOwningPlayerPawn());

		if (StatsInteraction)
		{
			WeaponInfo->SetStats(StatsInteraction);
		}

		WeaponInfo->SetVisibility(ESlateVisibility::Hidden);
	}
	if (WeaponMessages)
	{
		IWeaponInteraction* WeaponInteraction = GetOwningPlayerPawn()->FindComponentByInterface<IWeaponInteraction>();

		if (WeaponInteraction)
		{
			WeaponMessages->SetWeapon(WeaponInteraction);
		}
	}
}
