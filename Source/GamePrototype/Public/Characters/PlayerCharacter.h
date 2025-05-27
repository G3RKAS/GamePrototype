// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Pawn/ControllerInteraction.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;
class UReviveComponent;
class UCameraShakeComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API APlayerCharacter : public ABaseCharacter, public IControllerInteraction
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IControllerInteraction
	virtual void Possess(APawn*) override;
	virtual void StartCameraShake(TSubclassOf<UCameraShakeBase>, float);
	virtual void StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase>, bool);

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CameraAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CameraMoveAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (ClampMin = "0", UIMin = "0"))
	float MaxTargetArmLength;

	UPROPERTY(EditAnywhere, Category = Input, meta = (ClampMin = "0", UIMin = "0"))
	float MinTargetArmLength = 0;

	UPROPERTY(EditAnywhere, Category = Input, meta = (ClampMin = "0", UIMin = "0"))
	float ArmLengthMultiplier = 1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UReviveComponent* ReviveComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraShakeComponent* CameraShakeComponent;

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void CameraMove(const FInputActionValue& Value);
	void Shaking();
};
