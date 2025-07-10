// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GameLevelInfo.generated.h"

class UTextBlock;
class ILevelInteraction;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameLevelInfo : public UGameBaseUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> LevelNumber;

	ILevelInteraction* LevelInteraction;

	void UpdateLevel(uint8 InLevel = 0);
};
