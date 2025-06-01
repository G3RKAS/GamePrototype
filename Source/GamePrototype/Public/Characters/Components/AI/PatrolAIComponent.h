// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/AIComponent.h"
#include "PatrolAIComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UPatrolAIComponent : public UAIComponent
{
	GENERATED_BODY()
public:
	virtual void StartWork(AAIController*) override;
	virtual void StopWork() override;
	virtual void MoveFinished() override;
	
private:
	void MoveToPoint();
	FVector GetRandomPointToMove(FVector&);
	FTimerHandle MovingTimer;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "10", UIMin = "10"))
	float NavRadius = 2000;
};
