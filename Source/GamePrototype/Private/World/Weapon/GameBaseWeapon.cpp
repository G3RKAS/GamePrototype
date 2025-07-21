// (c) G3RKA. Game Prototype

#include "World/Weapon/GameBaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Core/Helpers/WeaponTableHelper.h"

AGameBaseWeapon::AGameBaseWeapon() : Super()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Staticmesh component"));
	check(StaticMeshComponent);
	SetRootComponent(StaticMeshComponent);
}

void AGameBaseWeapon::ChangeWeaponBasedOnName(FName InWeaponRowName)
{
	WeaponRow.RowName = InWeaponRowName;
	InitStaticMeshComponent();
}

void AGameBaseWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	WeaponRow.DataTable = FWeaponTableHelper::GetWeaponTable();
	if (!(WeaponRow.RowName.IsNone()))
	{
		InitStaticMeshComponent();
	}
}

void AGameBaseWeapon::InitStaticMeshComponent()
{
	check(StaticMeshComponent);
	StaticMeshComponent->SetStaticMesh(FWeaponTableHelper::GetWeaponStaticMesh(WeaponRow.RowName));
}
