// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Characters/PlayerVisionInteraction.h"
#include "Interfaces/AI/AIAttackInteraction.h"
#include "AnimalCharacter.generated.h"

class UHealthWidgetComponent;
class UAnimalWeaponComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AAnimalCharacter : public ABaseCharacter,
										   public IPlayerVisionInteraction,
										   public IAIAttackInteraction
{
	GENERATED_BODY()

public:
	AAnimalCharacter();

	virtual void OnCharacterDeath() override;
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
							  class AController* InstigatedBy, AActor* DamageCauser) override;

	// IStatsInteraction
	virtual float GetAttackDamage() override;
	virtual float GetAttackSpeed() override;
	virtual void SetAttackDamage(float) override;
	virtual void SetAttackSpeed(float) override;
	// IPlayerVisionInteraction
	virtual void CaughtInVision() override;
	virtual void LostInVision() override;
	// IAIAttackInteraction
	virtual void AttackEnemy(AActor*) override;
	virtual void ToggleSounds() override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings|XPGaining", meta = (ClampMin = "0", UIMin = "0"))
	float MultPerLevel = 1.1f;

	UPROPERTY(EditAnywhere, Category = "Settings|XPGaining", meta = (ClampMin = "0", UIMin = "0"))
	float XpGain = 200.f;

	UPROPERTY(EditAnywhere, Category = "Settings|Attack", meta = (ClampMin = "0", UIMin = "0"))
	float AttackDamage = 21.f;

	UPROPERTY(EditAnywhere, Category = "Settings|Attack", meta = (ClampMin = "0", UIMin = "0"))
	float AttackSpeed = 1.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UHealthWidgetComponent> HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAnimalWeaponComponent> AnimalWeaponComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComponent;
};
