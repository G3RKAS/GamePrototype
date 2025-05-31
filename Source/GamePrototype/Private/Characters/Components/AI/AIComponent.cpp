// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/AIComponent.h"
#include "AIController.h"

void UAIComponent::StartWork()
{

}

void UAIComponent::StopWork()
{

}

void UAIComponent::MoveFinished()
{

}

void UAIComponent::MoveToLocation(const FVector InLocation)
{
	check(AIController);
	AIController->MoveToLocation(InLocation);
}
