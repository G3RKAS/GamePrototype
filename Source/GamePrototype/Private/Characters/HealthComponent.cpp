// (c) G3RKA. Game Prototype

#include "Characters/HealthComponent.h"

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

void UHealthComponent::AddHealth(float InHealth)
{
	SetCurrentHealth(CurrentHealth + InHealth);
}

void UHealthComponent::SetCurrentHealth(float InCurrentHealth)
{
	CurrentHealth = FMath::Clamp(InCurrentHealth, 0, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
	if (FMath::IsNearlyZero(CurrentHealth))
	{
		OnDeath.Broadcast();
	}
	else
	{
		if (not(bIsRegeneratingHealth))
		{
			return;
		}
		if (FMath::IsNearlyEqual(CurrentHealth, MaxHealth))
		{
			GetWorld()->GetTimerManager().ClearTimer(RegenerationHandle);
		}
		else if (CurrentHealth < MaxHealth)
		{
			if (not(GetWorld()->GetTimerManager().IsTimerActive(RegenerationHandle)))
			{
				GetWorld()->GetTimerManager().SetTimer(RegenerationHandle, this, &ThisClass::RegenerateHealth,
													   RegeneratingRate, true);
			}
		}
	}
}

void UHealthComponent::RegenerateHealth()
{
	SetCurrentHealth(CurrentHealth + RegeneratingCount);
}
