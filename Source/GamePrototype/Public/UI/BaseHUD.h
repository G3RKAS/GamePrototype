// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
