// (c) G3RKA. Game Prototype


#include "UI/HUDWidget/GameHUDWidget.h"
#include "UI/BaseObjects/GamePlayerHealthBar.h"

void UGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (HealthBar)
	{
		HealthBar->SetBindType(EBindType::Owner);
	}
}
