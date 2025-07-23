// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackEndAnimNotify.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UAttackEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAttackEndAnimNotify();

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
						const FAnimNotifyEventReference& EventReference) override;
};
