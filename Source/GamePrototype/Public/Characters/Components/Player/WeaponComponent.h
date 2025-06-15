// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponChanged)

class AGameBaseWeapon;

UCLASS()
class GAMEPROTOTYPE_API UWeaponComponent : public UBaseActorComponent
{
	GENERATED_BODY()
public:
	void AddWeapon(FName);
	bool RemoveWeapon(FName);
	bool HasWeapon(FName);
	void EquipWeapon(FName);
	const AGameBaseWeapon* GetCurrentWeaponActor();

	FOnWeaponChanged& OnWeaponChanged();

private:
	UPROPERTY(EditAnywhere, Category = "Settings");
	TArray<FName> WeaponList;

	TObjectPtr<AGameBaseWeapon> WeaponActor;

	FName CurrentWeapon;

	FOnWeaponChanged OnWeaponChangedEvent;
};
