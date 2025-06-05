// (c) G3RKA. Game Prototype


#include "Characters/Components/AI/AttackAIComponent.h"
#include <Interfaces/Characters/StatsInteraction.h>

void UAttackAIComponent::StartWork(AAIController* InAIController)
{
	Super::StartWork(InAIController);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ThisClass::GoToEnemy, TimeToUpdateEnenmyLocation, true);
}

void UAttackAIComponent::StopWork()
{
	Super::StopWork();
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void UAttackAIComponent::MoveFinished(bool)
{
	AttackEnemy();
}

void UAttackAIComponent::SetEnemy(AActor* InAActor)
{
	Enemy = InAActor;
}

void UAttackAIComponent::GoToEnemy()
{
	check(Enemy);
	const FVector EnemyLocation(Enemy->GetActorLocation());

	MoveToLocation(EnemyLocation, AcceptableRadiusForMoving);
}

void UAttackAIComponent::AttackEnemy()
{
	if (not(GetWorldTimerManager().IsTimerActive(AttackTimer)))
	{
		return;
	}

	check(Enemy);
	const float DistanceBetweenActors = Enemy->GetDistanceTo(GetControlledPawn());

	if (DistanceBetweenActors > AcceptableRadiusForAttack)
	{
		return;
	}

	check(GetControlledPawn());
	const FVector ThisLocation = GetControlledPawn()->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	FRotator LookAtRotation = (TargetLocation - ThisLocation).Rotation();
	LookAtRotation.Pitch = 0.0f;
	LookAtRotation.Roll = 0.0f;

	GetControlledPawn()->SetActorRotation(LookAtRotation);

	IStatsInteraction* StatsInteraction = Cast<IStatsInteraction>(GetControlledPawn());

	UE_LOG(LogTemp, Warning, TEXT("Attack %s Damage %f"), *Enemy->GetName(), StatsInteraction->GetAttackDamage());
	PauseAttackTimer();

	FTimerHandle TimerDelay;
	GetWorldTimerManager().SetTimer(TimerDelay, this, &ThisClass::UnPauseAttackTimer, AttackCoolDown, false);
}

void UAttackAIComponent::PauseAttackTimer()
{
	GetWorldTimerManager().PauseTimer(AttackTimer);
}

void UAttackAIComponent::UnPauseAttackTimer()
{
	GetWorldTimerManager().UnPauseTimer(AttackTimer);
}
