// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

UINTERFACE(MinimalAPI)
class UHealthInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IHealthInteraction
{
	GENERATED_BODY()

public:
	virtual FOnDeathSignature& OnDeath() = 0;
	virtual FOnHealthChangedSignature& OnHealthChanged() = 0;
	virtual float GetHealthPercent() = 0;
};
