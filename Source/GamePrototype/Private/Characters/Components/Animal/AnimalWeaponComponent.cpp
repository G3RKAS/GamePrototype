// (c) G3RKA. Game Prototype


#include "Characters/Components/Animal/AnimalWeaponComponent.h"
#include "Interfaces/Characters/StatsInteraction.h"
#include "Engine/DamageEvents.h"

void UAnimalWeaponComponent::EquipWeapon(FName)
{
	return;
}

FName UAnimalWeaponComponent::GetCurrentWeaponName()
{
	return FName(GetOwner()->GetName() + "_Weapon");
}

bool UAnimalWeaponComponent::IsBlocking()
{
	return false;
}

FOnWeaponChangedSignature& UAnimalWeaponComponent::OnWeaponChanged()
{
	return OnWeaponChangedEvent;
}

FOnAnimNotifySignature& UAnimalWeaponComponent::OnWeaponAttackStart()
{
	return OnWeaponAttackStartEvent;
}

FOnAnimNotifySignature& UAnimalWeaponComponent::OnWeaponAttackEnd()
{
	return OnWeaponAttackEndEvent;
}

void UAnimalWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OnWeaponAttackStartEvent.AddUObject(this, &ThisClass::HandleAttack);
}

void UAnimalWeaponComponent::HandleAttack()
{
	FHitResult TraceHit;
	FVector TraceStart = GetOwner()->GetActorLocation();
	FVector TraceEnd = TraceStart + GetOwner()->GetActorForwardVector() * AttackRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

	FQuat CapsuleRotation = FRotationMatrix::MakeFromZ(GetOwner()->GetActorRightVector()).ToQuat();
	
	ECollisionChannel TraceChannel = UEngineTypes::ConvertToCollisionChannel(TraceTypeQuery);

	GetWorld()->SweepSingleByChannel(TraceHit, TraceStart, TraceEnd, CapsuleRotation, TraceChannel, CapsuleShape, Params);

	if (bIsShowTrace)
	{
		DrawDebugCapsule(GetWorld(), TraceEnd, CapsuleHalfHeight, CapsuleRadius, CapsuleRotation, FColor::Green, false,
						 2.0f);

		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
	}


	if (TraceHit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damaged %s"), *TraceHit.GetActor()->GetName());

		IStatsInteraction* StatsInteraction = Cast<IStatsInteraction>(GetOwner());

		TraceHit.GetActor()->TakeDamage(StatsInteraction->GetAttackDamage(), FDamageEvent(), nullptr, GetOwner());
	}
}
