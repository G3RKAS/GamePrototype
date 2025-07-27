// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/ReviveComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include <Interfaces/Characters/Player/WeaponInteraction.h>

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
	check(PlayerClass);
	check(!RevivePoints.IsEmpty());

	UE_LOG(LogTemp, Warning, TEXT("EXECUTE RESPAWN"))

	GetWorldTimerManager().SetTimer(TimerToRespawn, this, &ThisClass::RevivePlayer, TimeToRespawn, false);

}

void UReviveComponent::RevivePlayer()
{
	check(GetOwner());
	IControllerInteraction* ControllerInteraction = Cast<IControllerInteraction>(GetOwner());
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

	IWeaponInteraction* WeaponInteraction_OldPlayer = GetOwner()->FindComponentByInterface<IWeaponInteraction>();
	IWeaponInteraction* WeaponInteraction_NewPlayer = NewPlayer->FindComponentByInterface<IWeaponInteraction>();

	ControllerInteraction->Possess(NewPlayer);

	// Restore Level
	uint32 TotalOldXP = LevelInteraction_OldPlayer->GetTotalXP();
	LevelInteraction_NewPlayer->SetTotalXP(TotalOldXP - TotalOldXP * XpPercentLoss);
	// WeaponEquip
	WeaponInteraction_NewPlayer->EquipWeapon(WeaponInteraction_OldPlayer->GetCurrentWeaponName());

	UE_LOG(LogTemp, Warning, TEXT("RESPAWN"))

	GetOwner()->Destroy();
}
