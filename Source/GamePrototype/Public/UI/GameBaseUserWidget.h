// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameBaseUserWidget.generated.h"

UCLASS(Abstract)
class GAMEPROTOTYPE_API UGameBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	FTimerManager& GetWorldTimerManager();
};
