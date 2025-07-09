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

#include "Core/GameBaseWeapon.h"
#include "Characters/Components/Player/WeaponComponent.h"

#include "Characters/Components/Player/PlayerVisionComponent.h"

#include "Interfaces/Characters/HealthWidgetInteraction.h"

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

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon Component"));

	VisionComponent = CreateDefaultSubobject<UPlayerVisionComponent>(TEXT("Vision Component"));

	Tags.Add(FName("Player"));
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
	check(GetController());
	GetController()->Possess(InPawn);
}

void APlayerCharacter::StartCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, float Scale)
{
	check(GetController()) IShakeInteraction* ShakeInteraction = Cast<IShakeInteraction>(GetController());
	if (ShakeInteraction)
	{
		ShakeInteraction->StartCameraShake(ShakeClass, Scale);
	}
}

void APlayerCharacter::StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, bool bImmediately)
{
	check(GetController()) IShakeInteraction* ShakeInteraction = Cast<IShakeInteraction>(GetController());
	if (ShakeInteraction)
	{
		ShakeInteraction->StopAllInstancesOfCameraShake(ShakeClass, bImmediately);
	}
}

float APlayerCharacter::GetAttackDamage()
{
	if (WeaponComponent->GetCurrentWeaponActor())
	{
		return WeaponComponent->GetCurrentWeaponActor()->GetAttackDamage();
	}

	return 0.0f;
}

float APlayerCharacter::GetAttackSpeed()
{
	if (WeaponComponent->GetCurrentWeaponActor())
	{
		return WeaponComponent->GetCurrentWeaponActor()->GetAttackSpeed();
	}

	return 0.0f;
}

void APlayerCharacter::SetAttackDamage(float)
{
	return;
}

void APlayerCharacter::SetAttackSpeed(float)
{
	return;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	VisionComponent->OnVisionFind().AddUObject(this, &ThisClass::OnVisionFind);
	VisionComponent->OnVisionLost().AddUObject(this, &ThisClass::OnVisionLost);
	VisionComponent->StartWork(CameraComponent);
}

void APlayerCharacter::OnVisionFind(APawn* InFoundPawn)
{
	SwitchWidgetVision(true, InFoundPawn);
}

void APlayerCharacter::OnVisionLost(APawn* InLostPawn)
{
	SwitchWidgetVision(false, InLostPawn);
}

void APlayerCharacter::SwitchWidgetVision(bool InSwitch, APawn* InPawn)
{
	IHealthWidgetInteraction* WidgetInteraction = InPawn->FindComponentByInterface<IHealthWidgetInteraction>();
	if (WidgetInteraction)
	{
		WidgetInteraction->SetHealthVisibility(InSwitch);
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
	SpringArmComponent->TargetArmLength =
		FMath::Clamp(SpringArmComponent->TargetArmLength + MovementVector1D * ArmLengthMultiplier, MinTargetArmLength,
					 MaxTargetArmLength);
}

void APlayerCharacter::Shaking()
{
	CameraShakeComponent->MakeCameraShake();
}
