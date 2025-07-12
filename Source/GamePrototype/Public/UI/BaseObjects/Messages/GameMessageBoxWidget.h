// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GameMessageBoxWidget.generated.h"

class UGameMessageWidget;
class IWeaponInteraction;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameMessageBoxWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()
	
public:
	void SetWeapon(IWeaponInteraction*);

private:
	UPROPERTY(meta = (BindWidget));
	TObjectPtr<UPanelWidget> MessageBox;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UGameMessageWidget> MessageWidget;

	IWeaponInteraction* WeaponInteraction;

	void MakeMessage();
};
