// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/Messages/GameMessageBoxWidget.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "UI/BaseObjects/Messages/GameMessageWidget.h"
#include "Components/PanelWidget.h"

void UGameMessageBoxWidget::SetWeapon(IWeaponInteraction* InWeapon)
{
	check(InWeapon);
	WeaponInteraction = InWeapon;
	WeaponInteraction->OnWeaponChanged().AddUObject(this, &ThisClass::MakeMessage);
}

void UGameMessageBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check(MessageBox);
	MessageBox->ClearChildren();
}

void UGameMessageBoxWidget::MakeMessage()
{
	if (WeaponInteraction)
	{
		FName WeaponName = WeaponInteraction->GetCurrentWeaponName();

		UGameMessageWidget* Message = CreateWidget<UGameMessageWidget>(this, MessageWidget);
		check(Message)
		Message->SetPickUpWeapon(WeaponName);

		MessageBox->AddChild(Message);
	}
}
