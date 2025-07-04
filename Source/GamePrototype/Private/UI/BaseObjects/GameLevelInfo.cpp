// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/GameLevelInfo.h"
#include <Interfaces/Characters/LevelInteraction.h>
#include "Components/TextBlock.h"

void UGameLevelInfo::NativeConstruct()
{
	Super::NativeConstruct();
	LevelInteraction = GetOwningPlayerPawn()->FindComponentByInterface<ILevelInteraction>();
	if (LevelInteraction)
	{
		LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::UpdateLevel);
		UpdateLevel();
	}
}

void UGameLevelInfo::UpdateLevel(uint8)
{
	if (LevelInteraction)
	{
		LevelNumber->SetText(FText::AsNumber(LevelInteraction->GetLevel()));
	}
}