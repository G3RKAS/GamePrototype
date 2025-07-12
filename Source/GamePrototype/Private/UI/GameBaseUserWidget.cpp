// (c) G3RKA. Game Prototype


#include "UI/GameBaseUserWidget.h"

void UGameBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// TODO make update function on possess pawn;
	// TODO make delegate on possess
}

void UGameBaseUserWidget::DestroyWidgetWithAnimation()
{
	if (HideAnimation)
	{
		OnAnimationFinished.BindDynamic(this, &ThisClass::DestroyOnAnimationFinidshed);
		BindToAnimationFinished(HideAnimation, OnAnimationFinished);
		PlayAnimation(HideAnimation);
	}
	else
	{
		this->RemoveFromParent();
	}
}

FTimerManager& UGameBaseUserWidget::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void UGameBaseUserWidget::DestroyOnAnimationFinidshed()
{
	this->RemoveFromParent();
}

void UGameBaseUserWidget::UpdateWidgetOnPosses()
{
	SetVisibility(ESlateVisibility::Hidden);
}
