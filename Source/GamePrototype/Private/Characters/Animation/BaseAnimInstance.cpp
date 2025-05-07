// (c) G3RKA. Game Prototype


#include "Characters/Animation/BaseAnimInstance.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
	AnimInterface = Cast<IAnimInteraction>(Pawn);
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Pawn)
	{
		Speed = Pawn->GetVelocity().Size();
		
		if (AnimInterface)
		{
			bIsFalling = AnimInterface->IsFalling();
		}
	}
}
