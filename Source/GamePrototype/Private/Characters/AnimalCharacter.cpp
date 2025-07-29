// (c) G3RKA. Game Prototype


#include "Characters/AnimalCharacter.h"
#include "Characters/Components/HealthWidgetComponent.h"
#include "Characters/Components/Animal/AnimalWeaponComponent.h"

AAnimalCharacter::AAnimalCharacter() : Super()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	HealthWidgetComponent = CreateDefaultSubobject<UHealthWidgetComponent>(TEXT("Health Widget"));
	HealthWidgetComponent->SetupAttachment(GetMesh());

	AnimalWeaponComponent = CreateDefaultSubobject<UAnimalWeaponComponent>(TEXT("Animal Weapon Widget"));
}

void AAnimalCharacter::OnCharacterDeath()
{
	Super::OnCharacterDeath();
	GetController()->Destroy();
}

// IStatsInteraction
float AAnimalCharacter::GetAttackDamage()
{
	return AttackDamage;
}

float AAnimalCharacter::GetAttackSpeed()
{
	return AttackSpeed;
}

void AAnimalCharacter::SetAttackDamage(float InAttackDamage)
{
	AttackDamage = InAttackDamage;
}

void AAnimalCharacter::SetAttackSpeed(float InAttackSpeed)
{
	AttackSpeed = InAttackSpeed;
}

// IPlayerVisionInteraction
void AAnimalCharacter::CaughtInVision()
{
	HealthWidgetComponent->SetVisibility(true);
}

void AAnimalCharacter::LostInVision()
{
	HealthWidgetComponent->SetVisibility(false);
}

// IAIAttackInteraction
void AAnimalCharacter::AttackEnemy(AActor* InEnemy)
{
	Super::AttackEnemy(InEnemy);
}