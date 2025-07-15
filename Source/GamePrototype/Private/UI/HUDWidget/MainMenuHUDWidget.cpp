// (c) G3RKA. Game Prototype


#include "UI/HUDWidget/MainMenuHUDWidget.h"
#include "UI/BaseObjects/GameButton.h"
#include "Components/Button.h"
#include "Interfaces/Game/GameControl.h"

void UMainMenuHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check(NewGameButton);
	check(QuitGameButton);
	NewGameButton->OnClicked().AddDynamic(this, &ThisClass::OnNewGameClicked);
	QuitGameButton->OnClicked().AddDynamic(this, &ThisClass::OnQuitGameClicked);
}

void UMainMenuHUDWidget::OnNewGameClicked()
{
	IGameControl* GameControl = GetGameInstance<IGameControl>();
	check(GameControl)
	GameControl->NewGame();
}

void UMainMenuHUDWidget::OnQuitGameClicked()
{
	IGameControl* GameControl = GetGameInstance<IGameControl>();
	check(GameControl) GameControl->QuitGame(GetOwningPlayer());
}
