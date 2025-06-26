// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GamePlayerHealthBar.generated.h"

class UProgressBar;
class IHealthInteraction;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGamePlayerHealthBar : public UGameBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta =(BindWidget))
	UProgressBar* HealthProgressBar;

	IHealthInteraction* HealthInteraction;

	void HandleHealthChanged(float);

	void HandleLevelUp(uint8);

	void SetupHealth();
};
