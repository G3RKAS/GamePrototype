// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Characters/AnimInteraction.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API ABaseCharacter : public ACharacter, public IAnimInteraction
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual bool IsFalling() override;

protected:
	virtual void BeginPlay() override;

};
