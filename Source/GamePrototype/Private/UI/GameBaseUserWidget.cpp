// (c) G3RKA. Game Prototype


#include "UI/GameBaseUserWidget.h"

void UGameBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// TODO make update function on possess pawn;
	// TODO make delegate on possess
}

FTimerManager& UGameBaseUserWidget::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void UGameBaseUserWidget::UpdateWidgetOnPosses()
{

}
