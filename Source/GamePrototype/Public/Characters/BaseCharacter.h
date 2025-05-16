// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Characters/AnimInteraction.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "BaseCharacter.generated.h"

class UXPComponent;
class UHealthComponent;
class UStatsLevelingComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API ABaseCharacter : public ACharacter,
										 public IAnimInteraction,
										 public IStatsInteraction,
										 public ILevelInteraction
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	// IAnimInteraction
	virtual bool IsFalling() override;
	// IStatsInteraction
	virtual float GetMaxHealth() override;
	virtual float GetAttackDamage() override;
	virtual float GetAttackSpeed() override;
	virtual void SetMaxHealth(float) override;
	virtual void SetAttackDamage(float) override;
	virtual void SetAttackSpeed(float) override;
	// ILevelInteraction
	virtual int GetLevel() override;
	virtual OnLevelUpSignature& OnLevelUp() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UXPComponent* XPComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStatsLevelingComponent* StatsComponent;
};
