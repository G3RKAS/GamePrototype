// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "UI/GameBaseUserWidget.h"
#include "GameButton.generated.h"

class FOnButtonClickedEvent;
class UButton;
class UTextBlock;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameButton : public UGameBaseUserWidget
{
	GENERATED_BODY()
public:
	FOnButtonClickedEvent& OnClicked() const;

protected:
	virtual void NativePreConstruct() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	FText ButtonText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock;
};
