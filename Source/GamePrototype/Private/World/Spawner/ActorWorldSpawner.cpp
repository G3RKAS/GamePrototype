// (c) G3RKA. Game Prototype


#include "World/Spawner/ActorWorldSpawner.h"

#include "Components/BoxComponent.h"
#include <Interfaces/Characters/LevelInteraction.h>
#include "Kismet/KismetMathLibrary.h"

AActorWorldSpawner::AActorWorldSpawner()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	check(BoxComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AActorWorldSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (uint32 i{0}; i < ActorCount; ++i)
	{
		SpawnActorToWorld();
	}

	GetWorldTimerManager().SetTimer(ActorCheckUpTimer, this, &ThisClass::CheckUpActors, TimeToCheckOut, true);
}

void AActorWorldSpawner::CheckUpActors()
{
	const int ActorCountNow = SpawnedActors.Num();
	int ActorCheckedUpCount = 0;
	for (ActorCheckedUpCount; ActorCheckedUpCount < ActorCountNow; ++ActorCheckedUpCount)
	{
		if (!IsValid(SpawnedActors[ActorCheckedUpCount]))
		{
			SpawnedActors.RemoveAt(ActorCheckedUpCount);
			SpawnActorToWorld();
		}
	}
}

void AActorWorldSpawner::SpawnActorToWorld()
{
	check(GetWorld());
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetPointInWorld(), FRotator());
	if (SpawnedActor)
	{
		ILevelInteraction* LevelInteraction = SpawnedActor->FindComponentByInterface<ILevelInteraction>();

		if (LevelInteraction)
		{
			LevelInteraction->SetLevel(FMath::RandRange(ActorMinimunLevel, ActorMaximumLevel));
		}
		SpawnedActors.Add(SpawnedActor);
	}
	else
	{
		SpawnActorToWorld();
	}
}

FVector AActorWorldSpawner::GetPointInWorld()
{
	check(BoxComponent)
		const FTransform BoxTranform(BoxComponent->GetComponentRotation(), BoxComponent->GetComponentLocation(), FVector::OneVector);
	const FVector OriginalPoint =
		UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoxComponent->GetScaledBoxExtent());

	return UKismetMathLibrary::TransformLocation(BoxTranform, OriginalPoint);
}
