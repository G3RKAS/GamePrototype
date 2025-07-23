// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"
#include "WeaponComponent.generated.h"

class AGameAttackWeapon;

UCLASS()
class GAMEPROTOTYPE_API UWeaponComponent : public UBaseActorComponent, public IWeaponInteraction
{
	GENERATED_BODY()
public:
	virtual void EquipWeapon(FName) override;
	virtual FName GetCurrentWeaponName() override;
	virtual FOnWeaponChangedSignature& OnWeaponChanged() override;
	void SetEquipSceneComponent(USceneComponent*);
	bool HasWeapon(FName);

	float GetAttackDamage();
	float GetAttackSpeed();
	void SetAttackDamage(float);
	void SetAttackSpeed(float);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	FDataTableRowHandle StartWeapon;

	UPROPERTY()
	TObjectPtr<AGameAttackWeapon> WeaponActor;

	UPROPERTY()
	TObjectPtr<USceneComponent> EquipSceneComponent;

	FName CurrentWeapon;

	FOnWeaponChangedSignature OnWeaponChangedEvent;

	AGameAttackWeapon* GetCurrentWeaponActor();
	void InitStartWeapon();
	void CreateWeaponActor();
	void AttachToComponent();
};
