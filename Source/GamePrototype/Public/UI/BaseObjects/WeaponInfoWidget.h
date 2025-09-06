// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "WeaponInfoWidget.generated.h"

class ILevelInteraction;
class IWeaponInteraction;
class IStatsInteraction;
class UTextBlock;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UWeaponInfoWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()
	
public:
	void SetLevel(ILevelInteraction*);
	void SetWeapon(IWeaponInteraction*);
	void SetStats(IStatsInteraction*);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeaponInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DamageInfo;

	ILevelInteraction* LevelInteraction;
	IWeaponInteraction* WeaponInteraction;
	IStatsInteraction* StatsInteraction;

	void LevelHandler();
	void InitChangeWeaponInformation();
	void ChangeWeaponInformation(FName);
};
