// (c) G3RKA. Game Prototype

#include "UI/HUDWidget/GameHUDWidget.h"
#include "Interfaces/Controller/PlayerControllerInteraction.h"

#include "UI/BaseObjects/GameLevelInfo.h"

#include "UI/BaseObjects/GamePlayerLevelBar.h"

#include "UI/BaseObjects/GamePlayerHealthBar.h"

#include <Core/Helpers/WeaponTableHelper.h>
#include "UI/BaseObjects/WeaponInfoWidget.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "Interfaces/Characters/LevelInteraction.h"
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
		WeaponInfo->SetVisibility(ESlateVisibility::Hidden);

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
	}
	if (WeaponMessages)
	{
		IWeaponInteraction* WeaponInteraction = GetOwningPlayerPawn()->FindComponentByInterface<IWeaponInteraction>();

		if (WeaponInteraction)
		{
			WeaponInteraction->OnWeaponChanged().AddUObject(this, &ThisClass::HandleWeaponChange);
		}
	}
}

void UGameHUDWidget::HandleWeaponChange(FName InWeaponName)
{
	WeaponMessages->MakeMessage(
		FText::Format(PickUpMessageConcat, PickUpMessage, FWeaponTableHelper::GetWeaponName(InWeaponName)));
}
