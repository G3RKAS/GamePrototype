// (c) G3RKA. Game Prototype

#include "World/Weapon/GameAttackWeapon.h"
#include "Core/Helpers/WeaponTableHelper.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

AGameAttackWeapon::AGameAttackWeapon() : Super()
{
	SetActorEnableCollision(false);
}

float AGameAttackWeapon::GetAttackDamage()
{
	return WeaponAttackDamage;
}

float AGameAttackWeapon::GetAttackSpeed()
{
	return WeaponAttackSpeed;
}

void AGameAttackWeapon::SetAttackDamage(float InAttackDamage)
{
	WeaponAttackDamage = InAttackDamage;
}

void AGameAttackWeapon::SetAttackSpeed(float InAttackSpeed)
{
	WeaponAttackSpeed = InAttackSpeed;
}

void AGameAttackWeapon::ChangeWeaponBasedOnName(FName InWeaponRowName)
{
	Super::ChangeWeaponBasedOnName(InWeaponRowName);
	SetupWeaponStats();
}

void AGameAttackWeapon::StartAttack()
{
	SetActorEnableCollision(true);
}

void AGameAttackWeapon::EndAttack()
{
	SetActorEnableCollision(false);
	HittedActors.Empty();
}

void AGameAttackWeapon::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ActorOverlapWeapon);
	UE_LOG(LogTemp, Warning, TEXT("Binded"))
}

void AGameAttackWeapon::SetupWeaponStats()
{
	WeaponAttackDamage = FWeaponTableHelper::GetWeaponAttackDamage(WeaponRow.RowName);
	WeaponAttackSpeed = FWeaponTableHelper::GetWeaponAttackSpeed(WeaponRow.RowName);
}

void AGameAttackWeapon::ActorOverlapWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
										   const FHitResult& SweepResult)
{
	if (HittedActors.Contains(OtherActor))
	{
		return;
	}
	HittedActors.Add(OtherActor);
	UGameplayStatics::PlaySoundAtLocation(this, OnHitSound, GetActorLocation());
	OtherActor->TakeDamage(WeaponAttackDamage, FDamageEvent(), nullptr, GetOwner());

	UE_LOG(LogTemp, Warning, TEXT("Actor %s takes %f with %f attack speed in comp %s"), *OtherActor->GetName(),
		   WeaponAttackDamage, WeaponAttackSpeed, *OtherComp->GetName());
}
