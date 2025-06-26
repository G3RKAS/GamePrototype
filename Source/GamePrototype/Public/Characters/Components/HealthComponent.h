// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "Interfaces/Characters/HealthInteraction.h"
#include "HealthComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UHealthComponent : public UBaseActorComponent, public IHealthInteraction
{
	GENERATED_BODY()

public:
	float GetCurrentHealth();

	void AddHealth(float);

	float GetMaxHealth();

	void SetMaxHealth(float);

	virtual FOnDeathSignature& OnDeath() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health Settings", meta = (ClampMin = "0", UIMin = "0"))
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Health Settings", meta = (ClampMin = "0", UIMin = "0"))
	float CurrentHealth = MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Health Settings", meta = (AllowPrivateAccess = "true"))
	bool bIsRegeneratingHealth = false;
	UPROPERTY(EditAnywhere, Category = "Health Settings|Regenerating",
			  meta = (ClampMin = "0", UIMin = "0", EditCondition = "bIsRegeneratingHealth", EditConditionHides))
	float RegeneratingRate = 2.f;
	UPROPERTY(EditAnywhere, Category = "Health Settings|Regenerating",
			  meta = (ClampMin = "0", UIMin = "0", EditCondition = "bIsRegeneratingHealth", EditConditionHides))
	float RegeneratingCount = 10.f;

	FTimerHandle RegenerationHandle;

	FOnHealthChangedSignature OnHealthChangedEvent;

	FOnDeathSignature OnDeathEvent;

	void SetCurrentHealth(float);
	void RegenerateHealth();
};
