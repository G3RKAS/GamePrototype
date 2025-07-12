// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/Messages/GameMessageWidget.h"
#include "Components/TextBlock.h"
#include "Core/Helpers/WeaponTableHelper.h"

void UGameMessageWidget::NativeConstruct()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::DestroyWidgetWithAnimation, DelayToDelete, false);
}

void UGameMessageWidget::SetPickUpWeapon(FName InWeapon)
{
	check(MessageText);
	
	MessageText->SetText(FText::Format(NSLOCTEXT("UI", "PickUp Message Concat", "{0} {1}!"), PickUpText,
									   FWeaponTableHelper::GetWeaponName(InWeapon)));
}
