// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelUpSignature, uint8)
DECLARE_MULTICAST_DELEGATE(FOnXPUpSignature)

UINTERFACE(MinimalAPI)
class ULevelInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API ILevelInteraction
{
	GENERATED_BODY()

public:
	virtual float GetPercentLevel() = 0;
	virtual int GetLevel() = 0;
	virtual void SetLevel(int) = 0;
	virtual uint32 GetTotalXP() = 0;
	virtual void SetTotalXP(uint32) = 0;
	virtual FOnLevelUpSignature& OnLevelUp() = 0;
	virtual FOnXPUpSignature& OnXPUp() = 0;
};
