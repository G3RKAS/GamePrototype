// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatsInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStatsChangedSingature);

UINTERFACE(MinimalAPI)
class UStatsInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IStatsInteraction
{
	GENERATED_BODY()

public:
	virtual FOnStatsChangedSingature& OnStatsChanged() = 0;
	virtual float GetMaxHealth() = 0;
	virtual float GetAttackDamage() = 0;
	virtual float GetAttackSpeed() = 0;
	virtual void SetCurrentHealth(float) = 0;
	virtual void SetMaxHealth(float) = 0;
	virtual void SetAttackDamage(float) = 0;
	virtual void SetAttackSpeed(float) = 0;
};
