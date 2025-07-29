// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIAttackInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UAIAttackInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API IAIAttackInteraction
{
	GENERATED_BODY()

public:
	virtual void AttackEnemy(AActor*) = 0;
};
