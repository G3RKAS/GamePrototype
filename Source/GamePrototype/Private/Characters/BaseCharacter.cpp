// (c) G3RKA. Game Prototype

#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/Components/XPComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Characters/Components/StatsLevelingComponent.h"

#include "Components/CapsuleComponent.h"

ABaseCharacter::ABaseCharacter() : Super()
{
	XPComponent = CreateDefaultSubobject<UXPComponent>(TEXT("XPComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	StatsComponent = CreateDefaultSubobject<UStatsLevelingComponent>(TEXT("StatsLevelingComponent"));
}

// IAnimInteraction
bool ABaseCharacter::IsFalling()
{
	return GetCharacterMovement()->IsFalling();
}

bool ABaseCharacter::CanInteractWithWorld()
{
	return true;
}

float ABaseCharacter::GetAnimAttackLength()
{
	return AttackAnim->GetPlayLength();
}

// IStatsInteraction
float ABaseCharacter::GetMaxHealth()
{
	return HealthComponent->GetMaxHealth();
}

float ABaseCharacter::GetAttackDamage()
{
	return 0.0f;
}

float ABaseCharacter::GetAttackSpeed()
{
	return 0.0f;
}

void ABaseCharacter::SetCurrentHealth(float InCurrentHealth)
{
	HealthComponent->SetCurrentHealth(InCurrentHealth);
}

void ABaseCharacter::SetMaxHealth(float InMaxHealth)
{
	HealthComponent->SetMaxHealth(InMaxHealth);
}

void ABaseCharacter::SetAttackDamage(float)
{
	return;
}

void ABaseCharacter::SetAttackSpeed(float)
{
	return;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath().AddUObject(this, &ThisClass::OnCharacterDeath);
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeDamage);
}

void ABaseCharacter::OnCharacterDeath()
{
	check(GetMesh());
	UE_LOG(LogTemp, Warning, TEXT("DEAD %s"), *GetName());
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
								  AController* InstigatedBy, AActor* DamageCauser)
{
	if (HealthComponent->IsDead())
	{
		return;
	}

	HealthComponent->AddHealth(-1 * Damage);

	PlayAnimMontage(OnHitAnim);
}

void ABaseCharacter::AttackEnemy(AActor* InEnemy)
{
	if (!bIsAttacking)
	{
		check(GetMesh());
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		check(AnimInstance);

		bIsAttacking = true;

		FOnMontageEnded AttackEnded;
		AttackEnded.BindUObject(this, &ThisClass::OnAttackEnded);

		check(AttackAnim);
		PlayAnimMontage(AttackAnim, GetAttackSpeed());
		AnimInstance->Montage_SetEndDelegate(AttackEnded, AttackAnim);
	}
}

void ABaseCharacter::OnAttackEnded(UAnimMontage* InAnimMontage, bool bInterrupted)
{
	bIsAttacking = false;
}