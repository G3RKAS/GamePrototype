// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "WeaponInfoWidget.generated.h"

class IWeaponInteraction;
class IStatsInteraction;
class UTextBlock;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UWeaponInfoWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()
	
public:
	void SetWeapon(IWeaponInteraction*);
	void SetStats(IStatsInteraction*);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WeaponInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DamageInfo;

	IWeaponInteraction* WeaponInteraction;
	IStatsInteraction* StatsInteraction;

	void InitChangeWeaponInformation();
	void ChangeWeaponInformation();
};
