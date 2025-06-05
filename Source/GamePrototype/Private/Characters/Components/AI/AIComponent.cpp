// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/AIComponent.h"
#include "AIController.h"

void UAIComponent::StartWork(AAIController* InAIController)
{
	AIController = InAIController;
}

void UAIComponent::StopWork()
{
	AIController = nullptr;
}

void UAIComponent::MoveFinished(bool)
{

}

APawn* UAIComponent::GetControlledPawn()
{
	return AIController->GetPawn();
}

void UAIComponent::MoveToLocation(const FVector& InLocation)
{
	check(AIController);
	AIController->MoveToLocation(InLocation);
}
