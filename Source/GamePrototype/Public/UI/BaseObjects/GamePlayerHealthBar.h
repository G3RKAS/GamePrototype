// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "Interfaces/Characters/HealthWidgetInterface.h"
#include "GamePlayerHealthBar.generated.h"

class UProgressBar;
class IHealthInteraction;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGamePlayerHealthBar : public UGameBaseUserWidget, public IHealthWidgetInterface
{
	GENERATED_BODY()
public:
	virtual void SetBindType(AActor* InActorBind) override;

private:
	UPROPERTY(meta =(BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY()
	TObjectPtr<AActor> BindActor;

	IHealthInteraction* HealthInteraction;

	void SetupWidget();

	void HandleHealthChanged(float);

	void HandleLevelUp(uint8);

	void SetupHealth();
};
