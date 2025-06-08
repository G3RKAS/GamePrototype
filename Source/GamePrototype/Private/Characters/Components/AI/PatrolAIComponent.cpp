// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/PatrolAIComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"


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
	AIController->StopMovement();
	GetWorldTimerManager().SetTimer(MovingTimer, this, &ThisClass::MoveToPoint, WaitTime, false);
}

void UPatrolAIComponent::MoveToPoint()
{
	check(GetControlledPawn());
	FVector SourcePoint = GetControlledPawn()->GetActorLocation();
	FVector NextPoint = GetRandomPointToMove(SourcePoint);
	DrawDebugSphere(GetWorld(), NextPoint, 100.f, 10, FColor::Red, false, 5);
	MoveToLocation(NextPoint);
}

FVector UPatrolAIComponent::GetRandomPointToMove(FVector& InSourcePoint)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	check(NavSystem);
	FNavLocation NavResult;
	NavSystem->GetRandomPointInNavigableRadius(InSourcePoint, NavRadius, NavResult);

	return NavResult.Location;
}

