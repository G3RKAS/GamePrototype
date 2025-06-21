// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/WeaponComponent.h"
#include "Core/GameBaseWeapon.h"

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

		OnWeaponChangedEvent.Broadcast();
	}

	UE_LOG(LogTemp, Warning, TEXT("Weapon equiped %s"), *InWeaponName.ToString());
}

FName UWeaponComponent::GetCurrentWeaponName()
{
	return CurrentWeapon;
}

bool UWeaponComponent::HasWeapon(FName InWeaponName)
{
	return CurrentWeapon == InWeaponName;
}

AGameBaseWeapon* UWeaponComponent::GetCurrentWeaponActor()
{
	return WeaponActor;
}

FOnWeaponChanged& UWeaponComponent::OnWeaponChanged()
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