// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBaseWeapon.generated.h"

class UBoxComponent;

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
	float WeaponAttackDamage = 0.f;

	UPROPERTY(VisibleInstanceOnly, Category = "Settings")
	float WeaponAttackSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float PickUpTimeOut = 1.f;

	UFUNCTION()
	void PickUpWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle TimerHandle;

	void InitStaticMeshComponent();
	void InitWeaponStats();
	void EnableCollisions();
};
