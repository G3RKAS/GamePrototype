// (c) G3RKA. Game Prototype


#include "UI/BaseHUD.h"
#include "Blueprint/UserWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwningPawn())
	{
		UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), HUDShowWidget);
		check(UserWidget);
		UserWidget->AddToViewport();
	}
}
