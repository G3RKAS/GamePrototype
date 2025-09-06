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

	IAIAttackInteraction* AttackInteraction = Cast<IAIAttackInteraction>(GetControlledPawn());
	check(AttackInteraction);

	AttackInteraction->ToggleSounds();

	GetWorldTimerManager().SetTimer(AttackTimer, this, &ThisClass::GoToEnemy, TimeToUpdateEnemyLocation, true);
}

void UAttackAIComponent::StopWork()
{
	IAIAttackInteraction* AttackInteraction = Cast<IAIAttackInteraction>(GetControlledPawn());
	check(AttackInteraction);

	AttackInteraction->ToggleSounds();

	GetWorldTimerManager().ClearTimer(AttackTimer);
	GetWorldTimerManager().ClearTimer(RotationHandle);

	Super::StopWork();
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
	APawn* ControlledPawn = GetControlledPawn();

	const FVector ThisLocation = ControlledPawn->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	if (GetYawDiffInLook() < AttackAngle)
	{

		IStatsInteraction* StatsInteraction = Cast<IStatsInteraction>(ControlledPawn);
		check(StatsInteraction);

		IAIAttackInteraction* AttackInteraction = Cast<IAIAttackInteraction>(ControlledPawn);
		check(AttackInteraction);

		AttackInteraction->AttackEnemy(Enemy);

		IAnimInteraction* AnimInteraction = Cast<IAnimInteraction>(ControlledPawn);
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
	check(GetControlledPawn());
	APawn* ControlledPawn = GetControlledPawn();

	const FVector ThisLocation = ControlledPawn->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	FRotator LookingRotator = (Enemy->GetActorLocation() - ControlledPawn->GetActorLocation()).Rotation();

	return FMath::Abs(FMath::FindDeltaAngleDegrees(ControlledPawn->GetActorRotation().Yaw, LookingRotator.Yaw));
}

void UAttackAIComponent::RotateToEnemy()
{
	GetWorldTimerManager().SetTimer(RotationHandle, this, &ThisClass::UpdateRotation, TimeUpdateRotation, true);
}

void UAttackAIComponent::UpdateRotation()
{
	APawn* ControlledPawn = GetControlledPawn();

	if (!ControlledPawn)
	{
		return;
	}

	check(Enemy);
	const float DistanceBetweenActors = Enemy->GetDistanceTo(ControlledPawn);
	if (DistanceBetweenActors > AcceptableRadiusForAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is far away"));
		StartAttackingSequnece();
		return;
	}

	const FVector ThisLocation = ControlledPawn->GetActorLocation();
	const FVector TargetLocation = Enemy->GetActorLocation();

	const float OldRotationYaw = ControlledPawn->GetActorRotation().Yaw;

	FRotator NewRotator = (TargetLocation - ThisLocation).Rotation();
	NewRotator.Pitch = 0.0f;
	NewRotator.Roll = 0.0f;

	FRotator NewRotation = FMath::RInterpTo(ControlledPawn->GetActorRotation(), NewRotator,
											GetWorld()->GetDeltaSeconds(), AttackRotationSpeed);

	ControlledPawn->SetActorRotation(NewRotation);
	CurrentAttackRotation += FMath::Abs(FMath::FindDeltaAngleDegrees(OldRotationYaw, NewRotation.Yaw));

	UE_LOG(LogTemp, Warning, TEXT("CurrentRotation = %f"), CurrentAttackRotation);
	if ((CurrentAttackRotation >= AttackRotationTreshhold))
	{
		GetWorldTimerManager().ClearTimer(RotationHandle);

		FTimerHandle TimerDelay;
		GetWorldTimerManager().SetTimer(TimerDelay, this, &ThisClass::UnPauseAttackTimer, RotationCoolDown, false);

		return;
	}
	else if (GetYawDiffInLook() < AttackAngle)
	{
		StartAttackingSequnece();
		return;
	}
}

void UAttackAIComponent::StartAttackingSequnece()
{
	GetWorldTimerManager().ClearTimer(RotationHandle);
	UnPauseAttackTimer();
}

void UAttackAIComponent::PauseAttackTimer()
{
	GetWorldTimerManager().PauseTimer(AttackTimer);
}

void UAttackAIComponent::UnPauseAttackTimer()
{
	GetWorldTimerManager().UnPauseTimer(AttackTimer);
}
