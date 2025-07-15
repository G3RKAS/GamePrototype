// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameControl.generated.h"

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
};
