// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/HUDWidget/BaseHUDWidget.h"
#include "GameHUDWidget.generated.h"

class UGamePlayerHealthBar;
class UWeaponInfoWidget;
class UGameMessageBoxWidget;
class UPauseWidget;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional));
	TObjectPtr<UGamePlayerHealthBar> HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional));
	TObjectPtr<UWeaponInfoWidget> WeaponInfo;

	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional));
	TObjectPtr<UGameMessageBoxWidget> WeaponMessages;

	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional));
	TObjectPtr<UPauseWidget> PauseMenu;
};
