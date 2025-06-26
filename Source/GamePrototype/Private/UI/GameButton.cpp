// (c) G3RKA. Game Prototype


#include "UI/GameButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

FOnButtonClickedEvent& UGameButton::OnClicked() const
{
	check(Button);
	return Button->OnClicked;
}

void UGameButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (TextBlock)
	{
		TextBlock->SetText(ButtonText);
	}
}
