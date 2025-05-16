// (c) G3RKA. Game Prototype


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/XPComponent.h"
#include "Characters/HealthComponent.h"
#include "Characters/StatsLevelingComponent.h"

ABaseCharacter::ABaseCharacter() : Super()
{
	XPComponent = CreateDefaultSubobject<UXPComponent>(TEXT("XPComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	StatsComponent = CreateDefaultSubobject<UStatsLevelingComponent>(TEXT("StatsLevelingComponent"));
}

// IAnimInteraction
bool ABaseCharacter::IsFalling()
{
	return GetCharacterMovement()->IsFalling();
}

// ILevelInteraction
int ABaseCharacter::GetLevel()
{
	return XPComponent->GetLevel();
}

float ABaseCharacter::GetMaxHealth()
{
	return HealthComponent->GetMaxHealth();
}

float ABaseCharacter::GetAttackDamage()
{
	return 0.0f;
}

float ABaseCharacter::GetAttackSpeed()
{
	return 0.0f;
}

void ABaseCharacter::SetMaxHealth(float InMaxHealth)
{
	HealthComponent->SetMaxHealth(InMaxHealth);
}

void ABaseCharacter::SetAttackDamage(float)
{
	return;
}

void ABaseCharacter::SetAttackSpeed(float)
{
	return;
}

OnLevelUpSignature& ABaseCharacter::OnLevelUp()
{
	return XPComponent->OnLevelUp();
}
