// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UAnimInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IAnimInteraction
{
	GENERATED_BODY()

public:
	virtual bool IsFalling() = 0;
};