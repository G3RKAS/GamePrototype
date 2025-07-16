// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameControl.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLevelStartLoadingSignature);
DECLARE_MULTICAST_DELEGATE(FOnLevelLoadedSignature);

UINTERFACE(MinimalAPI)
class UGameControl : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IGameControl
{
	GENERATED_BODY()

public:
	virtual void NewGame() = 0;
	virtual void QuitGame(APlayerController*) = 0;
	virtual void LevelLoaded() = 0;
	virtual FOnLevelStartLoadingSignature& OnLevelStartLoading() = 0;
	virtual FOnLevelLoadedSignature& OnLevelLoaded() = 0;
};
