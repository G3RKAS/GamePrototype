// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/AIComponent.h"
#include "AIController.h"

void UAIComponent::StartWork(AAIController* InAIController)
{
	check(InAIController)
	AIController = InAIController;
}

void UAIComponent::StopWork()
{
	check(AIController)
	AIController->StopMovement();
	AIController = nullptr;
}

void UAIComponent::MoveFinished(const FPathFollowingResult&)
{

}

APawn* UAIComponent::GetControlledPawn()
{
	check(AIController);
	return AIController->GetPawn();
}

void UAIComponent::MoveToLocation(const FVector& InLocation, float AcceptanceRadius)
{
	check(AIController);
	AIController->MoveToLocation(InLocation, AcceptanceRadius);
}
