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

#include "World/Weapon/GameAttackWeapon.h"
#include "Characters/Components/Player/WeaponComponent.h"

#include "Characters/Components/Player/PlayerVisionComponent.h"

#include "Interfaces/Characters/PlayerVisionInteraction.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "Characters/Components/HealthComponent.h"

APlayerCharacter::APlayerCharacter() : Super()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	check(SpringArmComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	check(GetMesh());
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

	WeaponEquipSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Equip Scene Component"));
	check(WeaponEquipSceneComponent);
	WeaponEquipSceneComponent->SetupAttachment(GetMesh());
	check(WeaponComponent);
	WeaponComponent->SetEquipSceneComponent(WeaponEquipSceneComponent);

	VisionComponent = CreateDefaultSubobject<UPlayerVisionComponent>(TEXT("Vision Component"));

	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource Component"));

	Tags.Add(FName("Player"));
}

void APlayerCharacter::OnCharacterDeath()
{
	Super::OnCharacterDeath();
	GetCharacterMovement()->DisableMovement();
	check(StimuliSourceComponent);
	StimuliSourceComponent->UnregisterFromPerceptionSystem();
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
	if (AttackAction)
	{
		Input->BindAction(AttackAction, ETriggerEvent::Completed, this, &ThisClass::Attack);
	}
}

bool APlayerCharacter::CanInteractWithWorld()
{
	return not(IsFalling() || bIsAttacking);
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
	check(WeaponComponent);
	return WeaponComponent->GetAttackDamage();
}

float APlayerCharacter::GetAttackSpeed()
{
	check(WeaponComponent);
	return WeaponComponent->GetAttackSpeed();
}

void APlayerCharacter::SetAttackDamage(float InAttackDamage)
{
	check(WeaponComponent);
	WeaponComponent->SetAttackDamage(InAttackDamage);
}

void APlayerCharacter::SetAttackSpeed(float InAttackSpeed)
{
	check(WeaponComponent);
	WeaponComponent->SetAttackSpeed(InAttackSpeed);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(VisionComponent);
	VisionComponent->OnVisionFind().AddUObject(this, &ThisClass::OnVisionFind);
	VisionComponent->OnVisionLost().AddUObject(this, &ThisClass::OnVisionLost);
	VisionComponent->StartWork(CameraComponent);
}

void APlayerCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
									AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	if (HealthComponent->IsDead())
	{
		return;
	}

	CameraShakeComponent->MakeCameraShake();
}

void APlayerCharacter::AttackEnemy(AActor* InEnemy)
{
	if (!WeaponComponent->GetCurrentWeaponName().IsNone())
	{
		Super::AttackEnemy(InEnemy);
	}
}

void APlayerCharacter::OnAttackEnded(UAnimMontage* InAnimMontage, bool bInterrupted)
{
	Super::OnAttackEnded(InAnimMontage, bInterrupted);

	if (bInterrupted)
	{
		WeaponComponent->OnWeaponAttackEnd().Broadcast();
	}
}

void APlayerCharacter::OnVisionFind(APawn* InFoundPawn)
{
	IPlayerVisionInteraction* VisionInteraction = Cast<IPlayerVisionInteraction>(InFoundPawn);
	if (VisionInteraction)
	{
		VisionInteraction->CaughtInVision();
	}
}

void APlayerCharacter::OnVisionLost(APawn* InLostPawn)
{
	IPlayerVisionInteraction* VisionInteraction = Cast<IPlayerVisionInteraction>(InLostPawn);
	if (VisionInteraction)
	{
		VisionInteraction->LostInVision();
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

void APlayerCharacter::Attack()
{
	AttackEnemy(nullptr);
}

void APlayerCharacter::Shaking()
{
	CameraShakeComponent->MakeCameraShake();
}
