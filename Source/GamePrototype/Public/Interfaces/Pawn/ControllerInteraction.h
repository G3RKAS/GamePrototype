// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControllerInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UControllerInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IControllerInteraction
{
	GENERATED_BODY()

public:
	virtual void Possess(APawn*) = 0;
};
