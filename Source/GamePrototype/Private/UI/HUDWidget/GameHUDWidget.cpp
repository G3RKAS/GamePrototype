// (c) G3RKA. Game Prototype

#include "UI/HUDWidget/GameHUDWidget.h"
#include "Interfaces/Controller/PlayerControllerInteraction.h"

#include "UI/BaseObjects/GameLevelInfo.h"

#include "UI/BaseObjects/GamePlayerLevelBar.h"

#include "UI/BaseObjects/GamePlayerHealthBar.h"

#include "UI/BaseObjects/WeaponInfoWidget.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "Interfaces/Characters/StatsInteraction.h"

#include "UI/BaseObjects/Messages/GameMessageBoxWidget.h"

#include "UI/BaseObjects/Pause/PauseWidget.h"

void UGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetupPawnRelatedWidgets();

	IPlayerControllerInteraction* PlayerControllerInteraction = GetOwningPlayer<IPlayerControllerInteraction>();
	check(PlayerControllerInteraction);
	PlayerControllerInteraction->OnPlayerPosses().AddUObject(this, &ThisClass::SetupPawnRelatedWidgets);

	if (PauseMenu)
	{
		PlayerControllerInteraction->OnSwitchPauseWidget().AddUObject(PauseMenu, &ThisClass::SwitchVisibility);

		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGameHUDWidget::SetupPawnRelatedWidgets()
{
	if (LevelInfo)
	{
		LevelInfo->SetBindType(GetOwningPlayerPawn());
	}
	if (LevelBar)
	{
		LevelBar->SetBindType(GetOwningPlayerPawn());
	}
	if (HealthBar)
	{
		HealthBar->SetBindType(GetOwningPlayerPawn());
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
