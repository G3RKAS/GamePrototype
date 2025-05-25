// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
struct FInputActionValue;
class UReviveComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

private:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void CameraMove(const FInputActionValue& Value);

};
