// (c) G3RKA. Game Prototype

#include "UI/BaseObjects/GamePlayerLevelBar.h"
#include <Interfaces/Characters/LevelInteraction.h>
#include "Components/ProgressBar.h"

void UGamePlayerLevelBar::SetBindType(AActor* InActorBind)
{
	BindActor = InActorBind;
	SetupWidget();
}

void UGamePlayerLevelBar::SetupWidget()
{
	LevelInteraction = GetOwningPlayerPawn()->FindComponentByInterface<ILevelInteraction>();
	if (LevelInteraction)
	{
		LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::UpdateLevel);
		LevelInteraction->OnXPUp().AddUObject(this, &ThisClass::LevelHandler);
		GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ThisClass::LevelHandler));
	}
}

void UGamePlayerLevelBar::LevelHandler()
{
	UpdateLevel();
}

void UGamePlayerLevelBar::UpdateLevel(uint8)
{
	if (LevelInteraction)
	{
		LevelBar->SetPercent(LevelInteraction->GetPercentLevel());
	}
}