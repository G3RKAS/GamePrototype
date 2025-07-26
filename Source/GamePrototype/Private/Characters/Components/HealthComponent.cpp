// (c) G3RKA. Game Prototype

#include "Characters/Components/HealthComponent.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentHealth(CurrentHealth);
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::SetMaxHealth(float InMaxHealth)
{
	MaxHealth = InMaxHealth;
}

bool UHealthComponent::IsDead()
{
	return FMath::IsNearlyZero(CurrentHealth);
}

FOnDeathSignature& UHealthComponent::OnDeath()
{
	return OnDeathEvent;
}

FOnHealthChangedSignature& UHealthComponent::OnHealthChanged()
{
	return OnHealthChangedEvent;
}

float UHealthComponent::GetHealthPercent()
{
	return GetCurrentHealth()/GetMaxHealth();
}

void UHealthComponent::AddHealth(float InHealth)
{
	SetCurrentHealth(CurrentHealth + InHealth);
}

void UHealthComponent::SetCurrentHealth(float InCurrentHealth)
{
	if (CurrentHealth == InCurrentHealth)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(InCurrentHealth, 0, GetMaxHealth());

	OnHealthChangedEvent.Broadcast(CurrentHealth);
	if (FMath::IsNearlyZero(CurrentHealth))
	{
		OnDeathEvent.Broadcast();
	}
	else
	{
		check(GetWorld());
		if (not(bIsRegeneratingHealth))
		{
			return;
		}
		if (FMath::IsNearlyEqual(CurrentHealth, GetMaxHealth()))
		{
			GetWorldTimerManager().ClearTimer(RegenerationHandle);
		}
		else if (CurrentHealth < GetMaxHealth())
		{
			if (not(GetWorldTimerManager().IsTimerActive(RegenerationHandle)))
			{
				GetWorldTimerManager().SetTimer(RegenerationHandle, this, &ThisClass::RegenerateHealth,
													   RegeneratingRate, true);
			}
		}
	}
}

void UHealthComponent::RegenerateHealth()
{
	SetCurrentHealth(CurrentHealth + RegeneratingCount);
}
