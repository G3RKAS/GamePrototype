// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/CameraShakeComponent.h"
#include "Interfaces/Pawn/ControllerInteraction.h"

void UCameraShakeComponent::MakeCameraShake()
{
	if ((not(GetWorld()->GetTimerManager().IsTimerActive(TimerToRemoveShake))))
	{
		if (CameraShake)
		{
			ControllerInteraction = Cast<IControllerInteraction>(GetOwner());

			if (ControllerInteraction)
			{
				ControllerInteraction->StartCameraShake(CameraShake, ShakeScale);

				GetWorld()->GetTimerManager().SetTimer(TimerToRemoveShake, this, &ThisClass::StopCameraShake,
													   TimeToStopShaking, false);
			}
		}
	}
}

void UCameraShakeComponent::StopCameraShake()
{
	if (ControllerInteraction)
	{
		ControllerInteraction->StopAllInstancesOfCameraShake(CameraShake, false);
	}
}
