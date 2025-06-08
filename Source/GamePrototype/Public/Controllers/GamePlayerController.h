// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Controller/ShakeInteraction.h"
#include "GamePlayerController.generated.h"

class UInputMappingContext;

UCLASS(Abstract)
class GAMEPROTOTYPE_API AGamePlayerController : public APlayerController, public IShakeInteraction
{
	GENERATED_BODY()

public:
	// IShakeInteraction
	virtual void StartCameraShake(TSubclassOf<UCameraShakeBase>, float) override;
	virtual void StopAllInstancesOfCameraShake(TSubclassOf<UCameraShakeBase>, bool) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	virtual void BeginPlay() override;
};
