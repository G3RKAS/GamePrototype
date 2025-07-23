// (c) G3RKA. Game Prototype

#include "Characters/Components/Player/WeaponComponent.h"
#include "World/Weapon/GameAttackWeapon.h"

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
	OnWeaponChangedEvent.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Weapon equiped %s"), *InWeaponName.ToString());
}

FName UWeaponComponent::GetCurrentWeaponName()
{
	return CurrentWeapon;
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

FOnWeaponChangedSignature& UWeaponComponent::OnWeaponChanged()
{
	return OnWeaponChangedEvent;
}

void UWeaponComponent::SetEquipSceneComponent(USceneComponent* InEquipSceneComponent)
{
	EquipSceneComponent = InEquipSceneComponent;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::InitStartWeapon);
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
	WeaponActor = GetWorld()->SpawnActorDeferred<AGameAttackWeapon>(AGameAttackWeapon::StaticClass(),
																	FTransform::Identity, GetOwner(), nullptr,
																	ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (WeaponActor)
	{
		WeaponActor->FinishSpawning(FTransform::Identity);
		UE_LOG(LogTemp, Warning, TEXT("Created"))
		AttachToComponent();
	}
}

void UWeaponComponent::AttachToComponent()
{
	if (WeaponActor)
	{
		const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *EquipSceneComponent->GetName())
		WeaponActor->AttachToComponent(EquipSceneComponent, AttachmentRules);
	}
}
