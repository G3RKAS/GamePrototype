// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/PatrolAIComponent.h"
#include "AttackAIComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UAttackAIComponent : public UAIComponent
{
	GENERATED_BODY()
	
public:
	virtual void StartWork(AAIController*) override;
	virtual void StopWork() override;
	virtual void MoveFinished(const FPathFollowingResult&) override;
	void SetEnemy(AActor*);

private:
	void GoToEnemy();
	void AttackEnemy();

	void PauseAttackTimer();
	void UnPauseAttackTimer();

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float TimeToUpdateEnemyLocation = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))
	float AcceptableRadiusForMoving = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))
	float AcceptableRadiusForAttack = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float AttackCoolDown = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
	float AttackAngle = 15.0f;

	UPROPERTY()
	TObjectPtr<AActor> Enemy;

	FTimerHandle AttackTimer;
};
