// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/Pause/PauseWidget.h"
#include "UI/BaseObjects/GameButton.h"
#include "Components/Button.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
}

void UPauseWidget::ExitToMainMenuAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
}

void UPauseWidget::ExitFromGameAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
}
