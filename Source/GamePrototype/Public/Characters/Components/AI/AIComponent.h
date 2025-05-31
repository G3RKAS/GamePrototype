// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIComponent.generated.h"

class AAIController;

UCLASS(Abstract)
class GAMEPROTOTYPE_API UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void StartWork();
	virtual void StopWork();
	virtual void MoveFinished();

protected:
	void MoveToLocation(const FVector);
	
	AAIController* AIController;
};
