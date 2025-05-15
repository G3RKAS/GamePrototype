// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Characters/AnimInteraction.h"
#include "BaseCharacter.generated.h"

class UXPComponent;
class UHealthComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API ABaseCharacter : public ACharacter, public IAnimInteraction
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	// IAnimInteraction
	virtual bool IsFalling() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UXPComponent* XPComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UHealthComponent* HealthComponent;
};
