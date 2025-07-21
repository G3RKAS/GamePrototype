// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/WeaponComponent.h"
#include "World/Weapon/GameAttackWeapon.h"

void UWeaponComponent::EquipWeapon(FName InWeaponName)
{
	if (CurrentWeapon == InWeaponName)
	{
		return;
	}

	CurrentWeapon = InWeaponName;
	if (GetCurrentWeaponActor())
	{
		GetCurrentWeaponActor()->ChangeWeaponBasedOnName(InWeaponName);
	}

	UE_LOG(LogTemp, Warning, TEXT("Weapon equiped %s"), *InWeaponName.ToString());

	OnWeaponChangedEvent.Broadcast();
}

FName UWeaponComponent::GetCurrentWeaponName()
{
	return CurrentWeapon;
}

bool UWeaponComponent::HasWeapon(FName InWeaponName)
{
	return CurrentWeapon == InWeaponName;
}

AGameAttackWeapon* UWeaponComponent::GetCurrentWeaponActor()
{
	return WeaponActor;
}

FOnWeaponChangedSignature& UWeaponComponent::OnWeaponChanged()
{
	return OnWeaponChangedEvent;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	if (not(StartWeapon.RowName.IsNone()))
	{
		EquipWeapon(StartWeapon.RowName);
	}
}