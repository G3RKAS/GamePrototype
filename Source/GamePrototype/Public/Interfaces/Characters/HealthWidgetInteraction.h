// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthWidgetInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UHealthWidgetInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IHealthWidgetInteraction
{
	GENERATED_BODY()
public:
	virtual void SetHealthVisibility(bool) = 0;
};
