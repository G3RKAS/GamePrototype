// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/PlayerVisionComponent.h"
// #include <Interfaces/Characters/HealthWidgetInteraction.h>

void UPlayerVisionComponent::StartWork(USceneComponent* InVisionLocationComponent)
{
	VisionLocationComponent = InVisionLocationComponent;
	GetWorldTimerManager().SetTimer(VisionTimerHandle, this, &ThisClass::VisionHandle, VisionRate, true);
}

FOnVisionFindSignature& UPlayerVisionComponent::OnVisionFind()
{
	return OnVisionFindEvent;
}

FOnVisionLostSignature& UPlayerVisionComponent::OnVisionLost()
{
	return OnVisionLostEvent;
}

void UPlayerVisionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	for (APawn* PawnLost : VisibleActors)
	{
		OnVisionLostEvent.Broadcast(PawnLost);
	}
}

void UPlayerVisionComponent::VisionHandle()
{
	FVector VisionLocation = VisionLocationComponent->GetComponentLocation();

	FVector SphereTraceStart = VisionLocation;
	FVector SphereTraceEnd = VisionLocation;

	TArray<FHitResult> OutHits;

	bool bHit =
		UKismetSystemLibrary::SphereTraceMulti(GetWorld(), SphereTraceStart, SphereTraceEnd, VisionRadius,
											   TraceTypeQuery, false, TArray<AActor*>(), DrawDebugTrace, OutHits, true);
	if (bHit)
	{
		TSet<TObjectPtr<APawn>> NewPawns;
		for (FHitResult& HitResult : OutHits)
		{
			check(HitResult.GetActor());

			APawn* PawnFound = Cast<APawn>(HitResult.GetActor());

			if (PawnFound)
			{
				FVector LineTraceStart = VisionLocationComponent->GetComponentLocation();
				FVector LineTraceEnd = HitResult.GetActor()->GetActorLocation();
				FHitResult LineHit;

				UKismetSystemLibrary::LineTraceSingle(GetWorld(), LineTraceStart, LineTraceEnd, TraceTypeQuery, false,
													  TArray<AActor*>(), DrawDebugTrace, LineHit, true);

				if (LineHit.bBlockingHit)
				{
					check(LineHit.GetActor());
					if (LineHit.GetActor() == PawnFound)
					{
						NewPawns.Add(PawnFound);
					}
				}
			}
		}
		CheckForDiff(NewPawns);
	}
}

void UPlayerVisionComponent::CheckForDiff(TSet<TObjectPtr<APawn>> InNewPawns)
{
	TSet<TObjectPtr<APawn>> PawnsLost = VisibleActors.Difference(InNewPawns);
	TSet<TObjectPtr<APawn>> PawnsFound = InNewPawns.Difference(VisibleActors);
	for (APawn* PawnFound : PawnsFound)
	{
		OnVisionFindEvent.Broadcast(PawnFound);
		VisibleActors.Add(PawnFound);
	}
	for (APawn* PawnLost : PawnsLost)
	{
		OnVisionLostEvent.Broadcast(PawnLost);
		VisibleActors.Remove(PawnLost);
	}
}
