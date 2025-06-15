// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBaseWeapon.generated.h"

UCLASS()
class GAMEPROTOTYPE_API AGameBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameBaseWeapon();

	void ChangeWeaponBasedOnName(FName);

	float GetAttackDamage();
	float GetAttackSpeed();

	virtual void OnConstruction(const FTransform&);

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	FDataTableRowHandle WeaponRow;

	UPROPERTY(VisibleInstanceOnly, Category = "Settings")
	float WeaponAttackDamage = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Settings")
	float WeaponAttackSpeed = 0;

	void InitStaticMeshComponent();
	void InitWeaponStats();
};
