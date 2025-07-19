// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/Pause/PauseWidget.h"
#include "UI/BaseObjects/GameButton.h"
#include "Components/Button.h"

#include "Interfaces/Controller/PlayerControllerInteraction.h"

#include "Interfaces/Game/GameControl.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check(ContinueButton);
	check(ExitToMainMenuButton);
	check(ExitFromGameButton);
	ContinueButton->OnClicked().AddDynamic(this, &ThisClass::ContinueAction);
	ExitToMainMenuButton->OnClicked().AddDynamic(this, &ThisClass::ExitToMainMenuAction);
	ExitFromGameButton->OnClicked().AddDynamic(this, &ThisClass::ExitFromGameAction);
}

void UPauseWidget::ContinueAction()
{
	IPlayerControllerInteraction* PlayerControllerInteraction = Cast<IPlayerControllerInteraction>(GetOwningPlayer());
	check(PlayerControllerInteraction);
	PlayerControllerInteraction->ContinueGame();
}

void UPauseWidget::ExitToMainMenuAction()
{
	IGameControl* GameControl = GetGameInstance<IGameControl>();
	check(GameControl);
	GameControl->MainMenu();
}

void UPauseWidget::ExitFromGameAction()
{
	IGameControl* GameControl = GetGameInstance<IGameControl>();
	check(GameControl);
	GameControl->QuitGame(GetOwningPlayer());
}
