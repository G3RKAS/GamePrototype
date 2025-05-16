// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelInteraction.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnLevelUpSignature, uint8)

UINTERFACE(MinimalAPI)
class ULevelInteraction : public UInterface
{
	GENERATED_BODY()
};

class GAMEPROTOTYPE_API ILevelInteraction
{
	GENERATED_BODY()

public:
	virtual int GetLevel() = 0;
	virtual OnLevelUpSignature& OnLevelUp() = 0;
};
