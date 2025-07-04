// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/GamePlayerLevelBar.h"
#include <Interfaces/Characters/LevelInteraction.h>
#include "Components/ProgressBar.h"

void UGamePlayerLevelBar::NativeConstruct()
{
	Super::NativeConstruct();
	LevelInteraction = GetOwningPlayerPawn()->FindComponentByInterface<ILevelInteraction>();
	if (LevelInteraction)
	{
		LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::UpdateLevel);
		UpdateLevel();
	}
}

void UGamePlayerLevelBar::UpdateLevel(uint8)
{
	if (LevelInteraction)
	{
		LevelBar->SetPercent(LevelInteraction->GetPercentLevel());
	}
}