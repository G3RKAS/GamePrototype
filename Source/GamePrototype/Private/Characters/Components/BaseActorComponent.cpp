// (c) G3RKA. Game Prototype


#include "Characters/Components/BaseActorComponent.h"

FTimerManager& UBaseActorComponent::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}
