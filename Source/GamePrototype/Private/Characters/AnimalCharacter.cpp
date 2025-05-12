// (c) G3RKA. Game Prototype


#include "Characters/AnimalCharacter.h"
#include "Components/BoxComponent.h"

AAnimalCharacter::AAnimalCharacter() : Super()
{
	BoxColision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	check(BoxColision) 
	BoxColision->SetupAttachment(GetRootComponent());
}
