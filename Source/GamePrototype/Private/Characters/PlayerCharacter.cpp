// (c) G3RKA. Game Prototype


#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputComponent.h>
#include "InputAction.h"
#include <Kismet/KismetMathLibrary.h>

#include "Characters/Components/Player/ReviveComponent.h"
#include "Characters/Components/Player/CameraShakeComponent.h"
#include "Interfaces/Controller/ShakeInteraction.h"


APlayerCharacter::APlayerCharacter() : Super()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	check(SpringArmComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetMesh());
	MaxTargetArmLength = SpringArmComponent->TargetArmLength;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	check(CameraComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraShakeComponent = CreateDefaultSubobject<UCameraShakeComponent>(TEXT("Camera Shake Component"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 0, 480);
	bUseControllerRotationYaw = false;

	ReviveComponent = CreateDefaultSubobject<UReviveComponent>(TEXT("Revive Component"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(Input);
	if (CameraAction)
	{
		Input->BindAction(CameraAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
	if (MovementAction)
	{
		Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	}
	if (JumpAction)
	{
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	}
	if (CameraMoveAction)
	{
		Input->BindAction(CameraMoveAction, ETriggerEvent::Triggered, this, &ThisClass::CameraMove);
	}
}

// IControllerInteraction
void APlayerCharacter::Possess(APawn* InPawn)
{
	check(GetController())
	GetController()->Possess(InPawn);
}

void APlayerCharacter::StartCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, float Scale)
{
	check(GetController())
	IShakeInteraction* ShakeInteraction = Cast<IShakeInteraction>(GetController());
	if (ShakeInteraction)
	{
		ShakeInteraction->StartCameraShake(ShakeClass, Scale);
	}

}

void APlayerCharacter::StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, bool bImmediately)
{
	check(GetController())
	IShakeInteraction* ShakeInteraction = Cast<IShakeInteraction>(GetController());
	if (ShakeInteraction)
	{
		ShakeInteraction->StopAllInstancesOfCameraShake(ShakeClass, bImmediately);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		FRotator Rotation(0, GetControlRotation().Yaw, 0);

		AddMovementInput(UKismetMathLibrary::GetForwardVector(Rotation), MovementVector.Y);
		AddMovementInput(UKismetMathLibrary::GetRightVector(Rotation), MovementVector.X);
	}
}

void APlayerCharacter::CameraMove(const FInputActionValue& Value)
{
	float MovementVector1D = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));
	check(SpringArmComponent);
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + MovementVector1D * ArmLengthMultiplier, MinTargetArmLength,
					 MaxTargetArmLength);
}

void APlayerCharacter::Shaking()
{
	CameraShakeComponent->MakeCameraShake();
}
