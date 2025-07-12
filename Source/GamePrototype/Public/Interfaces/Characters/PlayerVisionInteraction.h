// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerVisionInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerVisionInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IPlayerVisionInteraction
{
	GENERATED_BODY()

public:
	virtual void CaughtInVision() = 0;
	virtual void LostInVision() = 0;
};
