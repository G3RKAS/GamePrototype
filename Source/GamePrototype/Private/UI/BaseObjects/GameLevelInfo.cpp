// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/GameLevelInfo.h"
#include <Interfaces/Characters/LevelInteraction.h>
#include "Components/TextBlock.h"

void UGameLevelInfo::SetBindType(AActor* InActorBind)
{
	BindActor = InActorBind;
	SetupWidget();
}

void UGameLevelInfo::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (FontSize > 0)
	{
		FSlateFontInfo FontInfo = LevelNumber->GetFont();
		FontInfo.Size = FontSize;
		LevelNumber->SetFont(FontInfo);
	}

}

void UGameLevelInfo::SetupWidget()
{
	LevelInteraction = BindActor->FindComponentByInterface<ILevelInteraction>();
	if (LevelInteraction)
	{
		LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::UpdateLevel);
		LevelInteraction->OnXPUp().AddUObject(this, &ThisClass::LevelHandler);
		UpdateLevel();
	}
}

void UGameLevelInfo::LevelHandler()
{
	UpdateLevel();
}

void UGameLevelInfo::UpdateLevel(uint8)
{
	if (LevelInteraction)
	{
		LevelNumber->SetText(FText::AsNumber(LevelInteraction->GetLevel()));
	}
}