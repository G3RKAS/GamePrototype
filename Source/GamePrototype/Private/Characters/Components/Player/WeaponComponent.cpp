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

AGameAttackWeapon* UWeaponComponent::GetCurrentWeaponActor()
{
	return WeaponActor;
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
		WeaponActor->AttachToComponent(EquipSceneComponent, AttachmentRules);
	}
}
