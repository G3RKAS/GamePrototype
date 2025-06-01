// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPROTOTYPE_API UBaseActorComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	FTimerManager& GetWorldTimerManager();
};
