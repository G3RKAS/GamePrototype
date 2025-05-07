// (c) G3RKA. Game Prototype


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter() : Super()
{
}

bool ABaseCharacter::IsFalling()
{
	return GetCharacterMovement()->IsFalling();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

