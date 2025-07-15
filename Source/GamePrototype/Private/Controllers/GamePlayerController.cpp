// (c) G3RKA. Game Prototype


#include "Controllers/GamePlayerController.h"
#include <EnhancedInputSubsystems.h>

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (DefaultMappingContext)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

// IShakeInteraction
void AGamePlayerController::StartCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, float Scale)
{
	check(PlayerCameraManager)
	PlayerCameraManager->StartCameraShake(ShakeClass, Scale);
}

void AGamePlayerController::StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, bool bImmediately)
{
	check(PlayerCameraManager)
	PlayerCameraManager->StopAllInstancesOfCameraShake(ShakeClass, bImmediately);
}
