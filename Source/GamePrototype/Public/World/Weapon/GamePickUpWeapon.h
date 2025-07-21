// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "World/Weapon/GameBaseWeapon.h"
#include "GamePickUpWeapon.generated.h"

UCLASS()
class GAMEPROTOTYPE_API AGamePickUpWeapon : public AGameBaseWeapon
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void PickUpWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float PickUpTimeOut = 1.f;

	FTimerHandle TimerHandle;

	void EnableCollisions();
};
