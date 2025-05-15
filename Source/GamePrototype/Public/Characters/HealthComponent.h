// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnHealthChangedSignature, float);
DECLARE_MULTICAST_DELEGATE(OnDeathSignature);

UCLASS()
class GAMEPROTOTYPE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	float GetCurrentHealth();
	float GetMaxHealth();

	void AddHealth(float);

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

	OnHealthChangedSignature OnHealthChanged;

	OnDeathSignature OnDeath;

	void SetCurrentHealth(float);
	void RegenerateHealth();
};
