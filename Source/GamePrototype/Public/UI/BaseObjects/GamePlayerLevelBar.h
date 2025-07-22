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
	TObjectPtr<UProgressBar> LevelBar;

	ILevelInteraction* LevelInteraction;

	void LevelHandler();

	void UpdateLevel(uint8 InLevel = 0);
};
