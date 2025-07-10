// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GameMessageWidget.generated.h"

class UTextBlock;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameMessageWidget : public UGameBaseUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetPickUpWeapon(FName);

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	FText PickUpText;

	UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = 0, UIMin = 0, Units = "s"))
	float DelayToDelete = 3.0f;
};
