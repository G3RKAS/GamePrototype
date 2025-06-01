// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseActorComponent.h"
#include "CameraShakeComponent.generated.h"

class IControllerInteraction;

UCLASS()
class GAMEPROTOTYPE_API UCameraShakeComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
	void MakeCameraShake();

private:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float ShakeScale = 1.f;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
	float TimeToStopShaking = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<UCameraShakeBase> CameraShake;

	FTimerHandle TimerToRemoveShake;

	IControllerInteraction* ControllerInteraction;

	void StopCameraShake();
};
