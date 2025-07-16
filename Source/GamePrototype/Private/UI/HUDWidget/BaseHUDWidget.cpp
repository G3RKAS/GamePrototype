// (c) G3RKA. Game Prototype


#include "UI/HUDWidget/BaseHUDWidget.h"
#include "UI/BaseObjects/Loading/LoadingScreenUserWidget.h"
#include "Interfaces/Game/GameControl.h"

void UBaseHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check(LoadingScreen);
	IGameControl* GameControl = GetGameInstance<IGameControl>();
	check(GameControl);
	GameControl->OnLevelStartLoading().AddUObject(LoadingScreen, &ThisClass::ShowWidget);
	GameControl->OnLevelLoaded().AddUObject(LoadingScreen, &ThisClass::HideWidgetWithAnimation);
}
