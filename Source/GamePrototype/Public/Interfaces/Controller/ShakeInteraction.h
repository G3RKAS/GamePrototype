// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShakeInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UShakeInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IShakeInteraction
{
	GENERATED_BODY()
public:
	virtual void StartCameraShake(TSubclassOf<UCameraShakeBase>, float) = 0;
	virtual void StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase>, bool) = 0;
};
