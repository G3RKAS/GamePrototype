// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "Interfaces/Characters/HealthWidgetInterface.h"
#include "GameAnimalInfo.generated.h"

class UGamePlayerHealthBar;
class UGameLevelInfo;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameAnimalInfo : public UGameBaseUserWidget, public IHealthWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void SetBindType(AActor* InActorBind) override;	

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGamePlayerHealthBar> HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameLevelInfo> LevelInfo;

	UPROPERTY()
	TObjectPtr<AActor> BindActor;

	void SetupWidget();
};
