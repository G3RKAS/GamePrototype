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
	virtual void QuitGame(APlayerController*) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSoftObjectPtr<UWorld> NewGameLevel;
};
