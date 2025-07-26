// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Controller/ShakeInteraction.h"
#include "Interfaces/Controller/PlayerControllerInteraction.h"
#include "GamePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AGamePlayerController : public APlayerController,
												public IShakeInteraction,
												public IPlayerControllerInteraction
{
	GENERATED_BODY()

public:
	// IShakeInteraction
	virtual void StartCameraShake(TSubclassOf<UCameraShakeBase>, float) override;
	virtual void StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase>, bool) override;
	// IPlayerControllerInteraction
	virtual void ContinueGame() override;
	virtual FOnSwitchWidgetSignature& OnSwitchPauseWidget() override;
	virtual FOnPossessSignature& OnPlayerPosses() override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> AllTimeMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> PauseAction;

	void TogglePause();

	void SwitchInputMode();

	bool bIsGamePaused = false;

	FOnSwitchWidgetSignature OnSwitchPauseWidgetEvent;

	FOnPossessSignature OnPossessEvent;
};
