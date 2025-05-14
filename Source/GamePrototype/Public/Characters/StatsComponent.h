// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnLevelUpSignature, uint8)

UCLASS()
class GAMEPROTOTYPE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	uint32 GetTotalXP();
	uint8 GetLevel();

	void virtual BeginPlay() override;
	void AddXPToTotal(int EXP);

private:
	uint32 GetXPForLevel(uint8);
	uint8 GetLevelFromXP(uint32);
	void UpdateLevel();

	uint32 XPTotalCount = 0;
	uint8 Level = 1;
	int XPOnLevelUP = 1000;

	OnLevelUpSignature OnLevelUp;
};
