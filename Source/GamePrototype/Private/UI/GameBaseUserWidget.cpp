// (c) G3RKA. Game Prototype

#include "UI/GameBaseUserWidget.h"

void UGameBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// TODO make update function on possess pawn;
	// TODO make delegate on possess
}

void UGameBaseUserWidget::SwitchVisibility()
{
	IsVisible() ? SetVisibility(ESlateVisibility::Hidden) : ShowWidget();
}

void UGameBaseUserWidget::ShowWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("VISIBLE"));
	SetVisibility(ESlateVisibility::Visible);
}

void UGameBaseUserWidget::HideWidgetWithAnimation()
{
	if (HideAnimation)
	{
		OnAnimationFinished.BindDynamic(this, &ThisClass::HideOnAnimationFinidshed);
		BindToAnimationFinished(HideAnimation, OnAnimationFinished);
		PlayAnimation(HideAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, true);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
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
		RemoveFromParent();
	}
}

FTimerManager& UGameBaseUserWidget::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void UGameBaseUserWidget::DestroyOnAnimationFinidshed()
{
	RemoveFromParent();
}

void UGameBaseUserWidget::HideOnAnimationFinidshed()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UGameBaseUserWidget::UpdateWidgetOnPosses()
{
	SetVisibility(ESlateVisibility::Hidden);
}
