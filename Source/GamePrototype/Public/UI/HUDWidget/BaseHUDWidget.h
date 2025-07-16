// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "BaseHUDWidget.generated.h"

class ULoadingScreenUserWidget;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UBaseHUDWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<ULoadingScreenUserWidget> LoadingScreen;
};
