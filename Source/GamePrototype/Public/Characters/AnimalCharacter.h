// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Characters/PlayerVisionInteraction.h"
#include "AnimalCharacter.generated.h"

class UHealthWidgetComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AAnimalCharacter : public ABaseCharacter, public IPlayerVisionInteraction //TODO ATTACK INTERFACE
{
	GENERATED_BODY()

public:
	AAnimalCharacter();

	virtual void OnCharacterDeath() override;

	// IStatsInteraction
	virtual float GetAttackDamage() override;
	virtual float GetAttackSpeed() override;
	virtual void SetAttackDamage(float) override;
	virtual void SetAttackSpeed(float) override;
	// IPlayerVisionInteraction
	virtual void CaughtInVision() override;
	virtual void LostInVision() override;
	//
	virtual void AttackEnemy(AActor*) override;

private:
	UPROPERTY(EditAnywhere, Category = "Attack Settings", meta = (ClampMin = "0", UIMin = "0"))
	float AttackDamage = 21.f;

	UPROPERTY(EditAnywhere, Category = "Attack Settings", meta = (ClampMin = "0", UIMin = "0"))
	float AttackSpeed = 1.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UHealthWidgetComponent> HealthWidgetComponent;
};
