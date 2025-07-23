// (c) G3RKA. Game Prototype


#include "Characters/Animation/Notifies/AttackEndAnimNotify.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"

UAttackEndAnimNotify::UAttackEndAnimNotify()
{
	bShouldFireInEditor = false;
}

void UAttackEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
								  const FAnimNotifyEventReference& EventReference)
{
	IWeaponInteraction* WeaponInteraction = MeshComp->GetOwner()->FindComponentByInterface<IWeaponInteraction>();
	check(WeaponInteraction);
	WeaponInteraction->OnWeaponAttackEnd().Broadcast();
}
