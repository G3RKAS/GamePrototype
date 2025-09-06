// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AnimalController.generated.h"

class UPatrolAIComponent;
class UAttackAIComponent;
class UAIComponent;

UCLASS()
class GAMEPROTOTYPE_API AAnimalController : public AAIController
{
	GENERATED_BODY()
public:
	AAnimalController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	virtual void OnMoveCompleted(FAIRequestID, const FPathFollowingResult&) override;
	virtual void OnPossess(APawn*) override;

private:
	UFUNCTION()
	void UpdateTargetInfo(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPatrolAIComponent> PatrolComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAttackAIComponent> AttackComponent;

	UPROPERTY()
	TObjectPtr<UAIComponent> CurrentComponentWork;
};
