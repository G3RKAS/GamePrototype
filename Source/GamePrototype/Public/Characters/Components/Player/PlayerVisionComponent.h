// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerVisionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisionFindSignature, APawn*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisionLostSignature, APawn*)

	UCLASS() class GAMEPROTOTYPE_API UPlayerVisionComponent : public UBaseActorComponent
{
	GENERATED_BODY()
public:
	void StartWork(USceneComponent*);

	FOnVisionFindSignature& OnVisionFind();
	FOnVisionLostSignature& OnVisionLost();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, Category = "Settings|Player Vision", meta = (ClampMin = "0", UIMin = "0"))
	float VisionRate = 0.5;

	UPROPERTY(EditAnywhere, Category = "Settings|Player Vision", meta = (ClampMin = "0", UIMin = "0"))
	float VisionRadius = 1200;

	UPROPERTY(EditAnywhere, Category = "Settings|Player Vision")
	TEnumAsByte<ETraceTypeQuery> TraceTypeQuery;

	UPROPERTY(EditAnywhere, Category = "Settings|Player Vision")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugTrace;

	TSet<TObjectPtr<APawn>> VisibleActors;

	FTimerHandle VisionTimerHandle;

private:
	FOnVisionFindSignature OnVisionFindEvent;

	FOnVisionLostSignature OnVisionLostEvent;

	USceneComponent* VisionLocationComponent;

	void VisionHandle();
	void CheckForDiff(TSet<TObjectPtr<APawn>>);
};
