// (c) G3RKA. Game Prototype


#include "Characters/Components/Player/WeaponComponent.h"

#include "Core/Helpers/WeaponTableHelper.h"
#include "Core/GameBaseWeapon.h"

void UWeaponComponent::AddWeapon(FName InWeaponName)
{
	if (not(FWeaponTableHelper::HasWeaponInTable(InWeaponName)))
	{
		checkNoEntry();
	}

	if (not(WeaponList.Contains(InWeaponName)))
	{
		WeaponList.Add(InWeaponName);
	}
}

bool UWeaponComponent::RemoveWeapon(FName InWeaponName)
{
	if (not(WeaponList.Contains(InWeaponName)))
	{
		return false;
	}

	WeaponList.Remove(InWeaponName);
	return true;
}

bool UWeaponComponent::HasWeapon(FName InWeaponName)
{
	return WeaponList.Contains(InWeaponName);
}

void UWeaponComponent::EquipWeapon(FName InWeaponName)
{
	if (not(WeaponList.Contains(InWeaponName)))
	{
		return;
	}

	CurrentWeapon = InWeaponName;
	WeaponActor->ChangeWeaponBasedOnName(InWeaponName);

	OnWeaponChangedEvent.Broadcast();
}

const AGameBaseWeapon* UWeaponComponent::GetCurrentWeaponActor()
{
	return WeaponActor;
}

FOnWeaponChanged& UWeaponComponent::OnWeaponChanged()
{
	return OnWeaponChangedEvent;
}
