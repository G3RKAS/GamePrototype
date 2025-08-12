// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/Messages/GameMessageWidget.h"
#include "Components/TextBlock.h"
#include "Core/Helpers/WeaponTableHelper.h"

void UGameMessageWidget::NativeConstruct()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::DestroyWidgetWithAnimation, DelayToDelete, false);
}

void UGameMessageWidget::SetText(FText InText)
{
	check(MessageText);
	
	MessageText->SetText(InText);
}
