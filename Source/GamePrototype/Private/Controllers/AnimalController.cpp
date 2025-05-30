// (c) G3RKA. Game Prototype

#include "Controllers/AnimalController.h"

AAnimalController::AAnimalController() : Super()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::UpdateTargetInfo);
}

void AAnimalController::UpdateTargetInfo(AActor* Actor, FAIStimulus Stimulus)
{
	if (not((Actor->Tags.Contains("Player"))))
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Update %s"), *Actor->GetName());
}
