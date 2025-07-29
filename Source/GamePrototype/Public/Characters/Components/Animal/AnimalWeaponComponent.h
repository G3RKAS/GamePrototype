// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "AnimalWeaponComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UAnimalWeaponComponent : public UBaseActorComponent, public IWeaponInteraction
{
	GENERATED_BODY()

public:
	// IWeaponInteraction
	virtual void EquipWeapon(FName) override;
	virtual FName GetCurrentWeaponName() override;
	virtual FOnWeaponChangedSignature& OnWeaponChanged() override;
	virtual FOnAnimNotifySignature& OnWeaponAttackStart() override;
	virtual FOnAnimNotifySignature& OnWeaponAttackEnd() override;

protected:
	virtual void BeginPlay() override;

private:
	void HandleAttack();

	FOnWeaponChangedSignature OnWeaponChangedEvent;
	FOnAnimNotifySignature OnWeaponAttackStartEvent;
	FOnAnimNotifySignature OnWeaponAttackEndEvent;
};
