// (c) G3RKA. Game Prototype

#include "Characters/Components/AI/AttackAIComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Interfaces/Characters/AnimInteraction.h"
#include "Interfaces/AI/AIAttackInteraction.h"
#include "Kismet/KismetMathLibrary.h"

void UAttackAIComponent::StartWork(AAIController* InAIController)
{
	Super::StartWork(InAIController);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ThisClass::GoToEnemy, TimeToUpdateEnemyLocation, true);
}

void UAttackAIComponent::StopWork()
{
	Super::StopWork();
	GetWorldTimerManager().ClearTimer(AttackTimer);
	GetWorldTimerManager().ClearTimer(RotationHandle);
}

void UAttackAIComponent::MoveFinished(const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Aborted)
	{
		return;
	}

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
	check(GetControlledPawn());

	const FVector ThisLocation = GetControlledPawn()->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	if (GetYawDiffInLook() < AttackAngle)
	{

		IStatsInteraction* StatsInteraction = Cast<IStatsInteraction>(GetControlledPawn());
		check(StatsInteraction);

		IAIAttackInteraction* AttackInteraction = Cast<IAIAttackInteraction>(GetControlledPawn());
		check(AttackInteraction);

		AttackInteraction->AttackEnemy(Enemy);

		IAnimInteraction* AnimInteraction = Cast<IAnimInteraction>(GetControlledPawn());
		check(AttackInteraction);

		float AdditionalTime = AnimInteraction ? AnimInteraction->GetAnimAttackLength() : 0.0f;

		PauseAttackTimer();

		FTimerHandle TimerDelay;
		GetWorldTimerManager().SetTimer(TimerDelay, this, &ThisClass::UnPauseAttackTimer,
										AttackCoolDown + AdditionalTime / StatsInteraction->GetAttackSpeed(), false);
	}
	else
	{
		PauseAttackTimer();
		CurrentAttackRotation = 0;
		RotateToEnemy();
	}
}

float UAttackAIComponent::GetYawDiffInLook()
{
	const FVector ThisLocation = GetControlledPawn()->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	FRotator LookingRotator = (Enemy->GetActorLocation() - GetControlledPawn()->GetActorLocation()).Rotation();

	return FMath::Abs(FMath::FindDeltaAngleDegrees(GetControlledPawn()->GetActorRotation().Yaw, LookingRotator.Yaw));
}

void UAttackAIComponent::RotateToEnemy()
{
	GetWorldTimerManager().SetTimer(RotationHandle, this, &ThisClass::UpdateRotation, TimeUpdateRotation, true);
}

void UAttackAIComponent::UpdateRotation()
{
	const FVector ThisLocation = GetControlledPawn()->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	const float OldRotationYaw = GetControlledPawn()->GetActorRotation().Yaw;

	FRotator NewRotator = (TargetLocation - ThisLocation).Rotation();
	NewRotator.Pitch = 0.0f;
	NewRotator.Roll = 0.0f;

	FRotator NewRotation = FMath::RInterpTo(GetControlledPawn()->GetActorRotation(), NewRotator,
											GetWorld()->GetDeltaSeconds(), AttackRotationSpeed);

	GetControlledPawn()->SetActorRotation(NewRotation);
	CurrentAttackRotation += FMath::Abs(OldRotationYaw - NewRotation.Yaw);

	UE_LOG(LogTemp, Warning, TEXT("CurrentRotation = %f"), CurrentAttackRotation);
	if ((CurrentAttackRotation >= AttackRotationTreshhold))
	{
		GetWorldTimerManager().ClearTimer(RotationHandle);

		FTimerHandle TimerDelay;
		GetWorldTimerManager().SetTimer(TimerDelay, this, &ThisClass::UnPauseAttackTimer, AttackCoolDown, false);

		return;
	}
	else if (GetYawDiffInLook() < AttackAngle)
	{
		GetWorldTimerManager().ClearTimer(RotationHandle);

		UnPauseAttackTimer();

		return;
	}
}

void UAttackAIComponent::PauseAttackTimer()
{
	GetWorldTimerManager().PauseTimer(AttackTimer);
}

void UAttackAIComponent::UnPauseAttackTimer()
{
	GetWorldTimerManager().UnPauseTimer(AttackTimer);
}
