// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/ReviveComponent.h"
#include "Characters/Components/HealthComponent.h"

void UReviveComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>();
	HealthComponent->OnDeath().AddUObject(this, &ThisClass::ExecuteRevive);
}

void UReviveComponent::ExecuteRevive()
{
	if (PlayerClass)
	{
		if (not(RevivePoints.IsEmpty()))
		{
			APawn* PlayerPawn = Cast<APawn>(GetOwner());

			if (PlayerPawn)
			{
				TArray<TSoftObjectPtr<ATargetPoint>> TempArray = RevivePoints.Array();

				int Index = FMath::RandHelper(TempArray.Num());
				FVector LocationToSpawn = TempArray[Index].Get()->GetActorLocation();

				check(GetWorld());

				GetWorld()->GetTimerManager().SetTimer(
					TimerToRespawn,
					[=, this]() {
						APlayerCharacter* NewPlayer =
							GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, LocationToSpawn, FRotator());
						PlayerPawn->GetController()->Possess(NewPlayer);
						GetOwner()->SetLifeSpan(0.1f);
					},
					TimeToRespawn, false);
			}
		}
	}
}
