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
class UAIPerceptionStimuliSourceComponent;

UCLASS(Abstract)
class GAMEPROTOTYPE_API APlayerCharacter : public ABaseCharacter, public IControllerInteraction
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void OnCharacterDeath() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IAnimInteraction
	virtual bool IsBlocking() override;
	virtual bool CanInteractWithWorld() override;
	// IControllerInteraction
	virtual void Possess(APawn*) override;
	virtual void StartCameraShake(TSubclassOf<UCameraShakeBase>, float) override;
	virtual void StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase>, bool) override;
	// IStatsInteraction
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

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> BlockAction;

	UPROPERTY(EditAnywhere, Category = "Settings|Block", meta = (ClampMin = "0", UIMin = "0", ClampMax = "180", UIMax = "180"))
	float AttackBlockingAngle = 90;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> WeaponEquipSceneComponent;

	UPROPERTY(EditAnywhere, Category = "Settings|Sounds")
	TObjectPtr<USoundBase> WeaponBlock;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UPlayerVisionComponent> VisionComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSourceComponent;

	virtual void BeginPlay() override;

	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
							  class AController* InstigatedBy, AActor* DamageCauser) override;

	virtual void AttackEnemy(AActor*) override;

	virtual void OnAttackEnded(UAnimMontage* InAnimMontage, bool bInterrupted) override;

private:
	bool bIsBlocking;

	// Vision Component
	void OnVisionFind(APawn*);
	void OnVisionLost(APawn*);

	// Movement
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);

	// Camera length movement
	void CameraMove(const FInputActionValue& Value);

	// Attack button
	void Attack();

	// Block button
	void StartBlock();
	void StopBlock();

	// Camera Shake Component
	void Shaking();

	// service func
	bool CanBlockDamage(FVector);
};
