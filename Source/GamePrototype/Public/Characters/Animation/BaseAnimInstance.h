// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/Characters/AnimInteraction.h"
#include "BaseAnimInstance.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsFalling;

private:
	UPROPERTY()
	APawn* Pawn;

	IAnimInteraction* AnimInterface;
};
