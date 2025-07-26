// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "XPComponent.generated.h"

UCLASS() 
class GAMEPROTOTYPE_API UXPComponent : public UBaseActorComponent, public ILevelInteraction
{
	GENERATED_BODY()

public:


	void AddXPToTotal(int EXP);

	// ILevelInteraction
	virtual float GetPercentLevel() override;
	virtual int GetLevel() override;
	virtual void SetLevel(int) override;
	virtual uint32 GetTotalXP() override;
	virtual void SetTotalXP(uint32) override;
	virtual FOnLevelUpSignature& OnLevelUp() override;
	virtual FOnXPUpSignature& OnXPUp() override;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", UIMin = "1"))
	uint8 Level = 1;

	uint32 GetXPForLevel(uint8);
	uint8 GetLevelFromXP(uint32);
	void UpdateLevel();

	uint32 XPTotalCount = 0;
	
	int XPOnLevelUP = 1000;

	FOnLevelUpSignature OnLevelUpEvent;
	FOnXPUpSignature OnXPUpEvent;
};
