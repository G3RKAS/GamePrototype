// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/HUDWidget/BaseHUDWidget.h"
#include "MainMenuHUDWidget.generated.h"

class UGameButton;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UMainMenuHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGameButton> NewGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameButton> QuitGameButton;

	UFUNCTION()
	void OnNewGameClicked();
	UFUNCTION()
	void OnQuitGameClicked();
};
