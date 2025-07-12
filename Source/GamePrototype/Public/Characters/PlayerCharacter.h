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
class UWeaponComponent;
class UPlayerVisionComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API APlayerCharacter : public ABaseCharacter, public IControllerInteraction
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IControllerInteraction
	virtual void Possess(APawn*) override;
	virtual void StartCameraShake(TSubclassOf<UCameraShakeBase>, float) override;
	virtual void StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase>, bool) override; 

	virtual float GetAttackDamage() override;
	virtual float GetAttackSpeed() override;
	virtual void SetAttackDamage(float) override;
	virtual void SetAttackSpeed(float) override;

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> CameraAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> CameraMoveAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (ClampMin = "0", UIMin = "0"))
	float MaxTargetArmLength;

	UPROPERTY(EditAnywhere, Category = Input, meta = (ClampMin = "0", UIMin = "0"))
	float MinTargetArmLength = 0;

	UPROPERTY(EditAnywhere, Category = Input, meta = (ClampMin = "0", UIMin = "0"))
	float ArmLengthMultiplier = 1;
	 
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UReviveComponent> ReviveComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UCameraShakeComponent> CameraShakeComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UPlayerVisionComponent> VisionComponent;

	virtual void BeginPlay() override;

private:
	void OnVisionFind(APawn*);
	void OnVisionLost(APawn*);
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void CameraMove(const FInputActionValue& Value);
	void Shaking();
};
