// (c) G3RKA. Game Prototype


#include "Characters/AnimalCharacter.h"
#include "Characters/Components/HealthWidgetComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Characters/Components/XPComponent.h"
#include "Characters/Components/Animal/AnimalWeaponComponent.h"
#include "Components/AudioComponent.h"
#include "Interfaces/Characters/LevelInteraction.h"

AAnimalCharacter::AAnimalCharacter() : Super()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	HealthWidgetComponent = CreateDefaultSubobject<UHealthWidgetComponent>(TEXT("Health Widget"));
	HealthWidgetComponent->SetupAttachment(GetMesh());

	AnimalWeaponComponent = CreateDefaultSubobject<UAnimalWeaponComponent>(TEXT("Animal Weapon Widget"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(GetRootComponent());
}

void AAnimalCharacter::OnCharacterDeath()
{
	Super::OnCharacterDeath();
	GetController()->Destroy();
}

void AAnimalCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
									AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	if (HealthComponent->IsDead())
	{
		ILevelInteraction* LevelInteraction = DamageCauser->FindComponentByInterface<ILevelInteraction>();
		check(LevelInteraction);
		UE_LOG(LogTemp, Warning, TEXT("Old XP %llu + %f"), LevelInteraction->GetTotalXP(),
			   XpGain * pow(MultPerLevel, XPComponent->GetLevel() - 1));
		LevelInteraction->SetTotalXP(LevelInteraction->GetTotalXP() +
									 XpGain * pow(MultPerLevel, XPComponent->GetLevel() - 1));
		UE_LOG(LogTemp, Warning, TEXT("New XP %llu"), LevelInteraction->GetTotalXP());
	}
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

void AAnimalCharacter::ToggleSounds()
{
	check(AudioComponent);
	if (AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
	else
	{
		AudioComponent->Play();
	}
}
