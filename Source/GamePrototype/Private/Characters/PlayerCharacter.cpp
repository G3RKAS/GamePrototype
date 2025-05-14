// (c) G3RKA. Game Prototype


#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputComponent.h>
#include "InputAction.h"
#include <Kismet/KismetMathLibrary.h>

#include "Characters/StatsComponent.h"

APlayerCharacter::APlayerCharacter() : Super()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	check(SpringArmComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetMesh());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	check(CameraComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 0, 480);
	bUseControllerRotationYaw = false;

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
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
