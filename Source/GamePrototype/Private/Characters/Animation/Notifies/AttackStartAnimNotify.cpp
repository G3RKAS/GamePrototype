// (c) G3RKA. Game Prototype


#include "Characters/Animation/Notifies/AttackStartAnimNotify.h"
#include "Interfaces/Characters/Player/WeaponInteraction.h"

UAttackStartAnimNotify::UAttackStartAnimNotify()
{
#if WITH_EDITOR
	bShouldFireInEditor = false;
#endif
}

void UAttackStartAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
									const FAnimNotifyEventReference& EventReference)
{
	IWeaponInteraction* WeaponInteraction = MeshComp->GetOwner()->FindComponentByInterface<IWeaponInteraction>();
	check(WeaponInteraction);
	WeaponInteraction->OnWeaponAttackStart().Broadcast();
}
