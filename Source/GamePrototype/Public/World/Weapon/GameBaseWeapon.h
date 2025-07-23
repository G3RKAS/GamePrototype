// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "World/GameWorldObject.h"
#include "GameBaseWeapon.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API AGameBaseWeapon : public AGameWorldObject
{
	GENERATED_BODY()
	
public:	
	AGameBaseWeapon();

	virtual void ChangeWeaponBasedOnName(FName);
protected:
	virtual void OnConstruction(const FTransform&) override;

	UPROPERTY(VisibleInstanceOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	FDataTableRowHandle WeaponRow;

private:
	void InitStaticMeshComponent();
};
