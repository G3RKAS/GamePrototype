// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/PatrolAIComponent.h"
#include "NavigationSystem.h"

void UPatrolAIComponent::StartWork(AAIController* InAIController)
{
	Super::StartWork(InAIController);
	// TODO Start moving
}

void UPatrolAIComponent::StopWork()
{
	Super::StopWork();
	// TODO Delete moving timer
}

void UPatrolAIComponent::MoveFinished()
{
	Super::MoveFinished();
	// TODO Move next
}

void UPatrolAIComponent::MoveToPoint()
{
	FVector SourcePoint = GetOwner()->GetActorLocation();
	FVector NextPoint = GetRandomPointToMove(SourcePoint);
	MoveToLocation(NextPoint);
}

FVector UPatrolAIComponent::GetRandomPointToMove(FVector& InSourcePoint)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FNavLocation NavResult;
	NavSystem->GetRandomPointInNavigableRadius(InSourcePoint, NavRadius, NavResult);

	return NavResult.Location;
}

