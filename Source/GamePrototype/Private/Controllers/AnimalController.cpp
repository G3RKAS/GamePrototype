// (c) G3RKA. Game Prototype

#include "Controllers/AnimalController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Characters/Components/AI/PatrolAIComponent.h"
#include "Characters/Components/AI/AttackAIComponent.h"

AAnimalController::AAnimalController() : Super()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	check(AIPerceptionComponent);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::UpdateTargetInfo);

	PatrolComponent = CreateDefaultSubobject<UPatrolAIComponent>(TEXT("Patrol Component"));

	AttackComponent = CreateDefaultSubobject<UAttackAIComponent>(TEXT("Attack Component"));
}

void AAnimalController::UpdateTargetInfo(AActor* Actor, FAIStimulus Stimulus)
{
	if (not((Actor->Tags.Contains("Player"))))
	{
		return;
	}

	CurrentComponentWork->StopWork();

	if (Stimulus.IsActive())
	{
		AttackComponent->SetEnemy(Actor);
		CurrentComponentWork = AttackComponent;
		CurrentComponentWork->StartWork(this);
	}
	else
	{
		CurrentComponentWork = PatrolComponent;
		CurrentComponentWork->StartWork(this);
	}

	UE_LOG(LogTemp, Warning, TEXT("Update %s Success = %d"), *Actor->GetName(), Stimulus.IsActive());
}

void AAnimalController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	check(CurrentComponentWork);
	CurrentComponentWork->MoveFinished(Result);
}

void AAnimalController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PatrolComponent->SetOriginPoint(InPawn->GetActorLocation());
	CurrentComponentWork = PatrolComponent;


	CurrentComponentWork->StartWork(this);
}
