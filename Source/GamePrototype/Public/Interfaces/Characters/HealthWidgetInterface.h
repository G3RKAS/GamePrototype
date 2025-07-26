// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthWidgetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHealthWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IHealthWidgetInterface
{
	GENERATED_BODY()

public: 
	virtual void SetBindType(AActor* InActorBind) = 0;
};
