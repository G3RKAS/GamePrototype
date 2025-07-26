// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GamePlayerLevelBar.generated.h"

class UProgressBar;
class ILevelInteraction;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGamePlayerLevelBar : public UGameBaseUserWidget
{
	GENERATED_BODY()
	
public:
	void SetBindType(AActor* InActorBind);

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> LevelBar;

	UPROPERTY()
	TObjectPtr<AActor> BindActor;

	ILevelInteraction* LevelInteraction;

	void SetupWidget();

	void LevelHandler();

	void UpdateLevel(uint8 InLevel = 0);
};
