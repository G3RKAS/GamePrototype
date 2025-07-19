// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/Game/GameControl.h"
#include "BaseGameInstance.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API UBaseGameInstance : public UGameInstance, public IGameControl
{
	GENERATED_BODY()
public:
	virtual void NewGame() override;
	virtual void MainMenu() override;
	virtual void QuitGame(APlayerController*) override;
	virtual void LevelLoaded() override;
	virtual FOnLevelStartLoadingSignature& OnLevelStartLoading() override;
	virtual FOnLevelLoadedSignature& OnLevelLoaded() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UWorld> NewGameLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float LoadingDelay = 0.5f;

	UPROPERTY()
	TSoftObjectPtr<UWorld> LoadingLevel;

	FOnLevelStartLoadingSignature OnLevelStartLoadingEvent;
	FOnLevelLoadedSignature OnLevelLoadedEvent;

	void StartLoadingLevel(const TSoftObjectPtr<UWorld>);
	void LoadLevel();
};
