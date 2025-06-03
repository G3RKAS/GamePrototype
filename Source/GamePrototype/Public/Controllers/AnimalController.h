// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AnimalController.generated.h"

class UPatrolAIComponent;
class UAIComponent;

UCLASS()
class GAMEPROTOTYPE_API AAnimalController : public AAIController
{
	GENERATED_BODY()
public:
	AAnimalController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAIPerceptionComponent* AIPerceptionComponent;

	virtual void OnMoveCompleted(FAIRequestID, const FPathFollowingResult&) override;
	virtual void OnPossess(APawn*) override;

private:
	UFUNCTION()
	void UpdateTargetInfo(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPatrolAIComponent* PatrolComponent;

	UPROPERTY()
	UAIComponent* CurrentComponentWork;
};
