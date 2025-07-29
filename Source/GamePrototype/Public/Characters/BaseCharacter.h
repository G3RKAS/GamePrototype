// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Characters/AnimInteraction.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "BaseCharacter.generated.h"

class UXPComponent;
class UHealthComponent;
class UStatsLevelingComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API ABaseCharacter : public ACharacter,
										 public IAnimInteraction,
										 public IStatsInteraction
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	// IAnimInteraction
	virtual bool IsFalling() override;
	virtual bool CanInteractWithWorld() override;
	virtual float GetAnimAttackLength() override;
	// IStatsInteraction
	virtual float GetMaxHealth() override;
	virtual float GetAttackDamage() override;
	virtual float GetAttackSpeed() override;
	virtual void SetCurrentHealth(float) override;
	virtual void SetMaxHealth(float) override;
	virtual void SetAttackDamage(float) override;
	virtual void SetAttackSpeed(float) override;

protected:
	bool bIsAttacking;

	virtual void BeginPlay() override;

	virtual void OnCharacterDeath();
	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
							  class AController* InstigatedBy, AActor* DamageCauser);

	virtual void AttackEnemy(AActor*);

	UFUNCTION()
	virtual void OnAttackEnded(UAnimMontage* InAnimMontage, bool bInterrupted);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UXPComponent> XPComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStatsLevelingComponent> StatsComponent;

	UPROPERTY(EditAnywhere, Category = "Settings|Attack")
	TObjectPtr<UAnimMontage> AttackAnim;
};
