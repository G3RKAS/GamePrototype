// (c) G3RKA. Game Prototype

#include "Characters/Animation/Notifies/Footstep.h"
#include "Kismet/GamePlayStatics.h"

void UFootstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
					   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	FHitResult OutHit;

	if (DoLineTrace(MeshComp, SocketName, OutHit))
	{
		UPhysicalMaterial* PhysMaterial = OutHit.PhysMaterial.Get();
		if (MaterialSounds.Contains(PhysMaterial))
		{
			UGameplayStatics::PlaySoundAtLocation(MeshComp, MaterialSounds[PhysMaterial], OutHit.Location);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(MeshComp, DefaultSound, OutHit.Location);
		}
	}
}

bool UFootstep::DoLineTrace(USkeletalMeshComponent* InMeshComp, FName InSocketName, FHitResult& InOutHit)
{
	check(InMeshComp);
	const FVector TraceStart = InMeshComp->GetSocketLocation(InSocketName);
	const FVector TraceEnd = TraceStart + FVector::DownVector * TraceDistance;

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(InMeshComp->GetOwner());
	TraceParams.bReturnPhysicalMaterial = true;

	check(InMeshComp->GetWorld());

	return InMeshComp->GetWorld()->LineTraceSingleByChannel(InOutHit, TraceStart, TraceEnd, ECC_Visibility,
															TraceParams);
}
