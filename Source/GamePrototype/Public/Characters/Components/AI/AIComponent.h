// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "AIComponent.generated.h"

class AAIController;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UAIComponent : public UBaseActorComponent
{
	GENERATED_BODY()

public:
	virtual void StartWork(AAIController*);
	virtual void StopWork();
	virtual void MoveFinished(bool);

protected:
	void MoveToLocation(const FVector&, float AcceptanceRadius = -1.0f);
	APawn* GetControlledPawn();

	AAIController* AIController;
};
