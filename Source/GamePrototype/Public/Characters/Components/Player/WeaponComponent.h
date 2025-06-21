// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "WeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponChanged)

class AGameBaseWeapon;

UCLASS()
class GAMEPROTOTYPE_API UWeaponComponent : public UBaseActorComponent, public IWeaponInteraction
{
	GENERATED_BODY()
public:
	virtual void EquipWeapon(FName) override;
	virtual FName GetCurrentWeaponName() override;
	bool HasWeapon(FName);
	AGameBaseWeapon* GetCurrentWeaponActor();

	FOnWeaponChanged& OnWeaponChanged();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	FDataTableRowHandle StartWeapon;

	UPROPERTY()
	TObjectPtr<AGameBaseWeapon> WeaponActor;

	FName CurrentWeapon;

	FOnWeaponChanged OnWeaponChangedEvent;
};
