// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/PatrolAIComponent.h"
#include "NavigationSystem.h"

void UPatrolAIComponent::StartWork(AAIController* InAIController)
{
	Super::StartWork(InAIController);

	GetWorldTimerManager().SetTimer(MovingTimer, this, &ThisClass::MoveToPoint, WaitTimeAfterSuccessMove, false);
}

void UPatrolAIComponent::StopWork()
{
	Super::StopWork();
	GetWorldTimerManager().ClearTimer(MovingTimer);
}

void UPatrolAIComponent::MoveFinished(bool bIsSuccess)
{
	Super::MoveFinished(bIsSuccess);
	
	float WaitTime = bIsSuccess ? WaitTimeAfterSuccessMove : WaitTimeAfterUnSuccessMove;

	GetWorldTimerManager().SetTimer(MovingTimer, this, &ThisClass::MoveToPoint, WaitTime, false);
}

void UPatrolAIComponent::MoveToPoint()
{
	FVector SourcePoint = GetControlledPawn()->GetActorLocation();
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

