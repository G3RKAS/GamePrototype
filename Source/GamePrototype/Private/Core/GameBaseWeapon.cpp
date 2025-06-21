// (c) G3RKA. Game Prototype

#include "Core/GameBaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Core/Helpers/WeaponTableHelper.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"

AGameBaseWeapon::AGameBaseWeapon() : Super()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Staticmesh component"));
	check(StaticMeshComponent);
	SetRootComponent(StaticMeshComponent);
}

void AGameBaseWeapon::PickUpWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AGameBaseWeapon::ChangeWeaponBasedOnName(FName InWeaponRowName)
{
	WeaponRow.RowName = InWeaponRowName;
	InitStaticMeshComponent();
	InitWeaponStats();
}

float AGameBaseWeapon::GetAttackDamage()
{
	return WeaponAttackDamage;
}

float AGameBaseWeapon::GetAttackSpeed()
{
	return WeaponAttackSpeed;
}

void AGameBaseWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	WeaponRow.DataTable = FWeaponTableHelper::GetWeaponTable();
	if (!(WeaponRow.RowName.IsNone()))
	{
		InitStaticMeshComponent();
		InitWeaponStats();
	}
}

void AGameBaseWeapon::InitStaticMeshComponent()
{
	check(StaticMeshComponent);
	StaticMeshComponent->SetStaticMesh(FWeaponTableHelper::GetWeaponStaticMesh(WeaponRow.RowName));
}

void AGameBaseWeapon::InitWeaponStats()
{
	WeaponAttackDamage = FWeaponTableHelper::GetWeaponAttackDamage(WeaponRow.RowName);
	WeaponAttackSpeed = FWeaponTableHelper::GetWeaponAttackSpeed(WeaponRow.RowName);
}

void AGameBaseWeapon::EnableCollisions()
{
	check(StaticMeshComponent);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
}
