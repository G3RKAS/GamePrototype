// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/ReviveComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Interfaces/Characters/LevelInteraction.h"

void UReviveComponent::BeginPlay()
{
	Super::BeginPlay();

	check(GetOwner());
	IHealthInteraction* HealthInteraction = GetOwner()->FindComponentByInterface<IHealthInteraction>();
	if (HealthInteraction)
	{
		HealthInteraction->OnDeath().AddUObject(this, &ThisClass::ExecuteRevivePlayer);
	}
}

void UReviveComponent::ExecuteRevivePlayer()
{
	if (PlayerClass)
	{
		if (not(RevivePoints.IsEmpty()))
		{
			GetWorldTimerManager().SetTimer(TimerToRespawn, this, &ThisClass::RevivePlayer, TimeToRespawn, false);
		}
	}
}

void UReviveComponent::RevivePlayer()
{
	check(GetOwner());
	IControllerInteraction* ControllerInteraction = GetOwner()->FindComponentByInterface<IControllerInteraction>();
	if (not(ControllerInteraction))
	{
		return;
	}

	TArray<TSoftObjectPtr<ATargetPoint>> TempArray = RevivePoints.Array();

	int Index = FMath::RandHelper(TempArray.Num());
	FVector LocationToSpawn = TempArray[Index].Get()->GetActorLocation();

	check(GetWorld());

	APlayerCharacter* NewPlayer = GetWorld()->SpawnActor<APlayerCharacter>(PlayerClass, LocationToSpawn, FRotator());
	ILevelInteraction* LevelInteraction_OldPlayer = GetOwner()->FindComponentByInterface<ILevelInteraction>();
	ILevelInteraction* LevelInteraction_NewPlayer = NewPlayer->FindComponentByInterface<ILevelInteraction>();

	ControllerInteraction->Possess(NewPlayer);

	// Restore Level
	LevelInteraction_NewPlayer->SetLevel(LevelInteraction_OldPlayer->GetLevel());
	// TODO
	// WeaponEquip

	GetOwner()->SetLifeSpan(0.1f);
}
