// (c) G3RKA. Game Prototype


#include "Characters/Components/Animal/AnimalWeaponComponent.h"

void UAnimalWeaponComponent::EquipWeapon(FName)
{
	return;
}

FName UAnimalWeaponComponent::GetCurrentWeaponName()
{
	return FName(GetOwner()->GetName() + "_Weapon");
}

FOnWeaponChangedSignature& UAnimalWeaponComponent::OnWeaponChanged()
{
	return OnWeaponChangedEvent;
}

FOnAnimNotifySignature& UAnimalWeaponComponent::OnWeaponAttackStart()
{
	return OnWeaponAttackStartEvent;
}

FOnAnimNotifySignature& UAnimalWeaponComponent::OnWeaponAttackEnd()
{
	return OnWeaponAttackEndEvent;
}

void UAnimalWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OnWeaponAttackStartEvent.AddUObject(this, &ThisClass::HandleAttack);
}

void UAnimalWeaponComponent::HandleAttack()
{
	//
}
