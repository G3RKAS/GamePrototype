// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "World/GameWorldObject.h"
#include "WorldBorder.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AWorldBorder : public AGameWorldObject
{
	GENERATED_BODY()

public:
	AWorldBorder();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Components")
	UBoxComponent* ExternalBoxCollision;

	UPROPERTY(EditInstanceOnly, Category = "Components") 
	UBoxComponent* InternalBoxCollision;

private:
	UPROPERTY()
	AActor* Player;
	UPROPERTY()
	FVector Location;

	UFUNCTION()
	void OnExternalAreaExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*
							OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnInternalAreaExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
