// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "WeaponComponent.generated.h"

class AGameBaseWeapon;

UCLASS()
class GAMEPROTOTYPE_API UWeaponComponent : public UBaseActorComponent, public IWeaponInteraction
{
	GENERATED_BODY()
public:
	virtual void EquipWeapon(FName) override;
	virtual FName GetCurrentWeaponName() override;
	virtual FOnWeaponChangedSignature& OnWeaponChanged() override;
	bool HasWeapon(FName);
	AGameBaseWeapon* GetCurrentWeaponActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	FDataTableRowHandle StartWeapon;

	UPROPERTY()
	TObjectPtr<AGameBaseWeapon> WeaponActor;

	FName CurrentWeapon;

	FOnWeaponChangedSignature OnWeaponChangedEvent;
};
