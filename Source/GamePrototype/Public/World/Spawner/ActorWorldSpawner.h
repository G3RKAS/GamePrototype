// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "World/GameWorldObject.h"
#include "ActorWorldSpawner.generated.h"

class UBoxComponent;

UCLASS()
class GAMEPROTOTYPE_API AActorWorldSpawner : public AGameWorldObject
{
	GENERATED_BODY()

public:
	AActorWorldSpawner();

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
	uint32 ActorCount = 0;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "s"))
	float TimeToCheckOut = 10.f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool bEnableLevelSettings;

	UPROPERTY(EditAnywhere, Category = "Settings|Level",
			  meta = (ClampMin = "1", UIMin = "1", EditCondition = "bEnableLevelSettings"))
	int32 ActorMinimunLevel = 1;

	UPROPERTY(EditAnywhere, Category = "Settings|Level",
			  meta = (ClampMin = "1", UIMin = "1", EditCondition = "bEnableLevelSettings"))
	int32 ActorMaximumLevel = 5;

	FTimerHandle ActorCheckUpTimer;

	void CheckUpActors();

	void SpawnActorToWorld();

	FVector GetPointInWorld();
};
