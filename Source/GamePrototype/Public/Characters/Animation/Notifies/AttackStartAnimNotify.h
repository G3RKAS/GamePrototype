// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackStartAnimNotify.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UAttackStartAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAttackStartAnimNotify();

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
						const FAnimNotifyEventReference& EventReference) override;
};
