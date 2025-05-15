// (c) G3RKA. Game Prototype


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/XPComponent.h"
#include "Characters/HealthComponent.h"

ABaseCharacter::ABaseCharacter() : Super()
{
	XPComponent = CreateDefaultSubobject<UXPComponent>(TEXT("XPComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}



bool ABaseCharacter::IsFalling()
{
	return GetCharacterMovement()->IsFalling();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

