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
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* LevelBar;

	ILevelInteraction* LevelInteraction;
	
	void TimerHandle();

	void UpdateLevel(uint8 InLevel = 0);
};
