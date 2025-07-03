// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GameHUDWidget.generated.h"

class UGamePlayerHealthBar;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameHUDWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional));
	TObjectPtr<UGamePlayerHealthBar> HealthBar;
};
