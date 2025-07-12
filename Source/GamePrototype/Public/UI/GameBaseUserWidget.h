// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameBaseUserWidget.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	virtual void DestroyWidgetWithAnimation();

	virtual void UpdateWidgetOnPosses();

	FTimerManager& GetWorldTimerManager();

private:
	UPROPERTY(Transient, meta=(BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> HideAnimation;

	FWidgetAnimationDynamicEvent OnAnimationFinished;

	UFUNCTION()
	void DestroyOnAnimationFinidshed();
};
