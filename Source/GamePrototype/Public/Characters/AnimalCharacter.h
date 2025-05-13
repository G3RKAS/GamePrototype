// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "AnimalCharacter.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AAnimalCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAnimalCharacter();
};
