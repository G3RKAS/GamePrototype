// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Engine/TargetPoint.h"
#include "Characters/PlayerCharacter.h"
#include "ReviveComponent.generated.h"

class UHealthComponent;


UCLASS()
class GAMEPROTOTYPE_API UReviveComponent : public UBaseActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	TSet<TSoftObjectPtr<ATargetPoint>> RevivePoints;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<APlayerCharacter> PlayerClass;

	UHealthComponent* HealthComponent;

	FTimerHandle TimerToRespawn;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float TimeToRespawn = 0.0f;

	void ExecuteRevive();

};
