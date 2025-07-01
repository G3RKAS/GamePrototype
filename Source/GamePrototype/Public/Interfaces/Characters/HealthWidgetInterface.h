// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthWidgetInterface.generated.h"

UENUM()
enum class EBindType : uint8
{
	Owner,
	Actor
};


UINTERFACE(MinimalAPI)
class UHealthWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IHealthWidgetInterface
{
	GENERATED_BODY()

public: 
	virtual void SetBindType(EBindType InBindType, AActor* InActorBind = nullptr) = 0;
};
