// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "XPComponent.generated.h"

UCLASS() 
class GAMEPROTOTYPE_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	uint32 GetTotalXP();
	uint8 GetLevel();

	void AddXPToTotal(int EXP);
	OnLevelUpSignature& OnLevelUp();

private:
	uint32 GetXPForLevel(uint8);
	uint8 GetLevelFromXP(uint32);
	void UpdateLevel();
	void SetTotalXP(uint32);

	uint32 XPTotalCount = 0;
	uint8 Level = 1;
	int XPOnLevelUP = 1000;

	OnLevelUpSignature OnLevelUpEvent;
};
