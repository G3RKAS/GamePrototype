// (c) G3RKA. Game Prototype


#include "Characters/Animation/BaseAnimInstance.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		AnimInterface = Cast<IAnimInteraction>(Pawn);
		WeaponInterface = Pawn->FindComponentByInterface<IWeaponInteraction>();
	}
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
		if (WeaponInterface)
		{
			bIsBlocking = WeaponInterface->IsBlocking();
		}
	}
}
