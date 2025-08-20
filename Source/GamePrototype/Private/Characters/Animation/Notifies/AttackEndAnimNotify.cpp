// (c) G3RKA. Game Prototype


#include "Characters/Animation/Notifies/AttackEndAnimNotify.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"

UAttackEndAnimNotify::UAttackEndAnimNotify()
{
#if WITH_EDITOR
	bShouldFireInEditor = false;
#endif
}

void UAttackEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
								  const FAnimNotifyEventReference& EventReference)
{
	IWeaponInteraction* WeaponInteraction = MeshComp->GetOwner()->FindComponentByInterface<IWeaponInteraction>();
	check(WeaponInteraction);
	WeaponInteraction->OnWeaponAttackEnd().Broadcast();
}
