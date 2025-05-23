// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnHealthChangedSignature, float);
DECLARE_MULTICAST_DELEGATE(OnDeathSignature);

UINTERFACE(MinimalAPI)
class UHealthInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IHealthInteraction
{
	GENERATED_BODY()

public:
	virtual OnDeathSignature& OnDeath() = 0;
};
