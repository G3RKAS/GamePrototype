// (c) G3RKA. Game Prototype


#include "Characters/AnimalCharacter.h"

AAnimalCharacter::AAnimalCharacter() : Super()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

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
