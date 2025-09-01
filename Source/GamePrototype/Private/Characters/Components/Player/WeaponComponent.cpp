// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/WeaponComponent.h"
#include "World/Weapon/GameAttackWeapon.h"

#include "Interfaces/Characters/AnimInteraction.h"

void UWeaponComponent::EquipWeapon(FName InWeaponName)
{
	if (CurrentWeapon == InWeaponName)
	{
		return;
	}

	if (GetCurrentWeaponActor())
	{
		GetCurrentWeaponActor()->ChangeWeaponBasedOnName(InWeaponName);
	}
	else
	{
		CreateWeaponActor();
		GetCurrentWeaponActor()->ChangeWeaponBasedOnName(InWeaponName);
	}

	CurrentWeapon = InWeaponName;
	OnWeaponChangedEvent.Broadcast(CurrentWeapon);
	UE_LOG(LogTemp, Warning, TEXT("Weapon equiped %s"), *InWeaponName.ToString());
}

FName UWeaponComponent::GetCurrentWeaponName()
{
	return CurrentWeapon;
}

bool UWeaponComponent::IsBlocking()
{
	return bIsBlocking;
}

FOnWeaponChangedSignature& UWeaponComponent::OnWeaponChanged()
{
	return OnWeaponChangedEvent;
}

FOnAnimNotifySignature& UWeaponComponent::OnWeaponAttackStart()
{
	return OnWeaponAttackStartEvent;
}

FOnAnimNotifySignature& UWeaponComponent::OnWeaponAttackEnd()
{
	return OnWeaponAttackEndEvent;
}

void UWeaponComponent::StartBlock()
{
	IAnimInteraction* AnimInteraction = Cast<IAnimInteraction>(GetOwner());
	
	check(AnimInteraction)
	if (!AnimInteraction->CanInteractWithWorld())
	{
		return;
	}
	if (GetCurrentWeaponName().IsNone())
	{
		return;
	}
	bIsBlocking = true;
}

void UWeaponComponent::StopBlock()
{
	bIsBlocking = false;
}

bool UWeaponComponent::CanBlockDamage(FVector InDamagePlace)
{
	if (!IsBlocking())
	{
		return false;
	}

	FRotator DamageLookingRotator = (InDamagePlace - GetOwner()->GetActorLocation()).Rotation();

	float AngleBEnemies =
		FMath::Abs(FMath::FindDeltaAngleDegrees(GetOwner()->GetActorRotation().Yaw, DamageLookingRotator.Yaw));

	UE_LOG(LogTemp, Warning, TEXT("Angle %f"), AngleBEnemies)

	return AngleBEnemies <= AttackBlockingAngle;
}

void UWeaponComponent::SetEquipSceneComponent(USceneComponent* InEquipSceneComponent)
{
	EquipSceneComponent = InEquipSceneComponent;
}

bool UWeaponComponent::HasWeapon(FName InWeaponName)
{
	return CurrentWeapon == InWeaponName;
}

float UWeaponComponent::GetAttackDamage()
{
	if (GetCurrentWeaponActor())
	{
		return GetCurrentWeaponActor()->GetAttackDamage();
	}
	return 0.0f;
}

float UWeaponComponent::GetAttackSpeed()
{
	if (GetCurrentWeaponActor())
	{
		return GetCurrentWeaponActor()->GetAttackSpeed();
	}
	return 0.0f;
}

void UWeaponComponent::SetAttackDamage(float InAttackDamage)
{
	if (GetCurrentWeaponActor())
	{
		GetCurrentWeaponActor()->SetAttackDamage(InAttackDamage);
	}
}

void UWeaponComponent::SetAttackSpeed(float InAttackSpeed)
{
	if (GetCurrentWeaponActor())
	{
		GetCurrentWeaponActor()->SetAttackSpeed(InAttackSpeed);
	}
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::InitStartWeapon);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type InEndPlayReason)
{
	Super::EndPlay(InEndPlayReason);
	if (GetCurrentWeaponActor())
	{
		GetCurrentWeaponActor()->Destroy();
	}
}

AGameAttackWeapon* UWeaponComponent::GetCurrentWeaponActor()
{
	return WeaponActor;
}

void UWeaponComponent::InitStartWeapon()
{
	if (not(StartWeapon.RowName.IsNone()))
	{
		EquipWeapon(StartWeapon.RowName);
	}
}

void UWeaponComponent::CreateWeaponActor()
{
	check(GetWorld());
	check(WeaponClass);
		
	WeaponActor = GetWorld()->SpawnActorDeferred<AGameAttackWeapon>(
		WeaponClass, FTransform::Identity, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (WeaponActor)
	{
		WeaponActor->FinishSpawning(FTransform::Identity);
		UE_LOG(LogTemp, Warning, TEXT("Created"))

		AttachToComponent();

		OnWeaponAttackStartEvent.AddUObject(WeaponActor, &AGameAttackWeapon::StartAttack);
		OnWeaponAttackEndEvent.AddUObject(WeaponActor, &AGameAttackWeapon::EndAttack);
		UE_LOG(LogTemp, Warning, TEXT("Binded"))
	}
}

void UWeaponComponent::AttachToComponent()
{
	if (WeaponActor)
	{
		const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		UE_LOG(LogTemp, Warning, TEXT("Attached"))
		WeaponActor->AttachToComponent(EquipSceneComponent, AttachmentRules);
	}
}
