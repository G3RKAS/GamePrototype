// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/Messages/GameMessageBoxWidget.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "UI/BaseObjects/Messages/GameMessageWidget.h"
#include "Components/PanelWidget.h"

void UGameMessageBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check(MessageBox);
	MessageBox->ClearChildren();
}

void UGameMessageBoxWidget::MakeMessage(FText InMessage)
{
	UGameMessageWidget* Message = CreateWidget<UGameMessageWidget>(this, MessageWidget);
	check(Message) Message->SetText(InMessage);

	MessageBox->AddChild(Message);
}
