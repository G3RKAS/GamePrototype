// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "AnimalCharacter.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AAnimalCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	virtual float GetAttackDamage() override;
	virtual float GetAttackSpeed() override;
	virtual void SetAttackDamage(float) override;
	virtual void SetAttackSpeed(float) override;

private:
	UPROPERTY(EditAnywhere, Category = "Attack Settings", meta = (ClampMin = "0", UIMin = "0"))
	float AttackDamage = 21.f;

	UPROPERTY(EditAnywhere, Category = "Attack Settings", meta = (ClampMin = "0", UIMin = "0"))
	float AttackSpeed = 1.f;
};
