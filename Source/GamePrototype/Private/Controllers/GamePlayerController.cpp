// (c) G3RKA. Game Prototype


#include "Controllers/GamePlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (DefaultMappingContext)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	if (AllTimeMappingContext)
	{
		Subsystem->AddMappingContext(AllTimeMappingContext, 0);
	}
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	check(Input);
	if (PauseAction)
	{
		Input->BindAction(PauseAction, ETriggerEvent::Completed, this, &ThisClass::TogglePause);
	}
}

void AGamePlayerController::TogglePause()
{
	bIsGamePaused = !bIsGamePaused;
	SetPause(bIsGamePaused);
	SwitchInputMode();
	OnSwitchPauseWidgetEvent.Broadcast();
}

void AGamePlayerController::SwitchInputMode()
{
	bShowMouseCursor = bIsGamePaused;
	if (bShowMouseCursor)
	{
		SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(true));
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
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

// IPlayerControllerInteraction
void AGamePlayerController::ContinueGame()
{
	TogglePause();
}

FOnSwitchWidgetSignature& AGamePlayerController::OnSwitchPauseWidget()
{
	return OnSwitchPauseWidgetEvent;
}
