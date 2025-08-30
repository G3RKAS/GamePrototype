// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Footstep.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API UFootstep : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
						const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category = "Settings|Sounds")
	TMap<TObjectPtr<UPhysicalMaterial>, TObjectPtr<USoundBase>> MaterialSounds;

	UPROPERTY(EditAnywhere, Category = "Settings|Sounds")
	TObjectPtr<USoundBase> DefaultSound;

	UPROPERTY(EditAnywhere, Category = "Settings|Trace")
	FName SocketName;

	const float TraceDistance = 50.0f;

	bool DoLineTrace(USkeletalMeshComponent*, FName, FHitResult&);
};
