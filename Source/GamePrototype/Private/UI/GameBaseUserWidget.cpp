// (c) G3RKA. Game Prototype


#include "UI/GameBaseUserWidget.h"

FTimerManager& UGameBaseUserWidget::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}
