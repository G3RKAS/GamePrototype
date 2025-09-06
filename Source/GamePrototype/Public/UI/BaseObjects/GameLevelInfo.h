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

public:
	void SetBindType(AActor* InActorBind);

protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "128", UIMax = "128"))
	uint32 FontSize;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> LevelNumber;

	UPROPERTY()
	TObjectPtr<AActor> BindActor;

	ILevelInteraction* LevelInteraction;

	void SetupWidget();

	void LevelHandler();

	void UpdateLevel(uint8 InLevel = 0);
};
