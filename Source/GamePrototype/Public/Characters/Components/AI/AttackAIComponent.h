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

	float GetYawDiffInLook();

	void RotateToEnemy();
	void UpdateRotation();

	void StartAttackingSequnece();
	void PauseAttackTimer();
	void UnPauseAttackTimer();

	UPROPERTY(EditAnywhere, Category = "Settings|Moving", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float TimeToUpdateEnemyLocation = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Settings|Moving", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))
	float AcceptableRadiusForMoving = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Moving", meta = (ClampMin = "0", UIMin = "0", Units = "cm"))
	float AcceptableRadiusForAttack = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Enemy", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float AttackCoolDown = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Settings|Enemy", meta = (ClampMin = "0", UIMin = "0"))
	float AttackAngle = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Rotation", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float RotationCoolDown = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Settings|Enemy", meta = (ClampMin = "0", UIMin = "0"))
	float AttackRotationSpeed = 55.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Rotation", meta = (ClampMin = "0", UIMin = "0"))
	float AttackRotationTreshhold = 180.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Rotation", meta = (ClampMin = "0", UIMin = "0"))
	float TimeUpdateRotation = 0.1f;

	UPROPERTY()
	TObjectPtr<AActor> Enemy;

	float CurrentAttackRotation;

	FTimerHandle AttackTimer;

	FTimerHandle RotationHandle;
};
