// (c) G3RKA. Game Prototype

#include "Controllers/AnimalController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Characters/Components/AI/PatrolAIComponent.h"

AAnimalController::AAnimalController() : Super()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::UpdateTargetInfo);

	PatrolComponent = CreateDefaultSubobject<UPatrolAIComponent>(TEXT("Patrol Component Component"));
}

void AAnimalController::UpdateTargetInfo(AActor* Actor, FAIStimulus Stimulus)
{
	if (not((Actor->Tags.Contains("Player"))))
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Update %s"), *Actor->GetName());
}

void AAnimalController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	bool bIsSuccess = Result.IsSuccess();
	CurrentComponentWork->MoveFinished(bIsSuccess);
}

void AAnimalController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CurrentComponentWork = PatrolComponent;
	CurrentComponentWork->StartWork(this);
}
