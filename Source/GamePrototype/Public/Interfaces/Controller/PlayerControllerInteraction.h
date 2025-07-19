// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllerInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSwitchWidgetSignature)

UINTERFACE(MinimalAPI)
class UPlayerControllerInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IPlayerControllerInteraction
{
	GENERATED_BODY()

public:
	virtual void ContinueGame() = 0;
	virtual FOnSwitchWidgetSignature& OnSwitchPauseWidget() = 0;
};
