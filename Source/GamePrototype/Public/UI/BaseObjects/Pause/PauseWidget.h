// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "PauseWidget.generated.h"

class UGameButton;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UPauseWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameButton> ContinueButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameButton> ExitToMainMenuButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameButton> ExitFromGameButton;

	UFUNCTION()
	void ContinueAction();

	UFUNCTION()
	void ExitToMainMenuAction();

	UFUNCTION()
	void ExitFromGameAction();
};
