// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AnimalController.generated.h"

UCLASS()
class GAMEPROTOTYPE_API AAnimalController : public AAIController
{
	GENERATED_BODY()
public:
	AAnimalController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent;

private:
	UFUNCTION()
	void UpdateTargetInfo(AActor* Actor, FAIStimulus Stimulus);
};
