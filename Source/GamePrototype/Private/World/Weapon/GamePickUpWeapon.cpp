// (c) G3RKA. Game Prototype


#include "World/Weapon/GamePickUpWeapon.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"

void AGamePickUpWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(StaticMeshComponent);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::PickUpWeapon);
}

void AGamePickUpWeapon::PickUpWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								   const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("--------------"));
	UE_LOG(LogTemp, Warning, TEXT("Overlap %s"), *WeaponRow.RowName.ToString());
	IWeaponInteraction* WeaponInteraction = OtherActor->FindComponentByInterface<IWeaponInteraction>();
	if (WeaponInteraction)
	{
		FName OldName = WeaponRow.RowName;
		if (not(WeaponInteraction->GetCurrentWeaponName().IsNone()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Changed"));
			ChangeWeaponBasedOnName(WeaponInteraction->GetCurrentWeaponName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Deleted"));
			SetLifeSpan(0.1f);
		}
		check(StaticMeshComponent);
		StaticMeshComponent->SetGenerateOverlapEvents(false);
		WeaponInteraction->EquipWeapon(OldName);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::EnableCollisions, PickUpTimeOut, false);
	}
}

void AGamePickUpWeapon::EnableCollisions()
{
	check(StaticMeshComponent);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
}
