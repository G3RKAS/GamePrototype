// (c) G3RKA. Game Prototype


#include "Core/GameBaseWeapon.h"
#include "Core/Helpers/WeaponTableHelper.h"

AGameBaseWeapon::AGameBaseWeapon() : Super()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Staticmesh component"));
	check(StaticMeshComponent)
	SetRootComponent(StaticMeshComponent);
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
