// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelScriptActor.generated.h"

UCLASS()
class GAMEPROTOTYPE_API AGameLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	void DelayLoadLevel();
};
