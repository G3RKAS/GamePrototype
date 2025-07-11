// (c) G3RKA. Game Prototype


#include "UI/GameBaseUserWidget.h"

void UGameBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// TODO make update function on possess pawn;
	// TODO make delegate on possess
}

void UGameBaseUserWidget::HideWidgetWithAnimation()
{
	if (HideAnimation)
	{
		OnAnimationFinished.BindDynamic(this, &ThisClass::HideOnAnimationFinidshed);
		BindToAnimationFinished(HideAnimation, OnAnimationFinished);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

FTimerManager& UGameBaseUserWidget::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void UGameBaseUserWidget::HideOnAnimationFinidshed()
{
}

void UGameBaseUserWidget::UpdateWidgetOnPosses()
{
	SetVisibility(ESlateVisibility::Hidden);
}
