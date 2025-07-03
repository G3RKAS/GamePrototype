// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/Characters/HealthWidgetInteraction.h"
#include "HealthWidgetComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UHealthWidgetComponent : public UWidgetComponent, public IHealthWidgetInteraction
{
	GENERATED_BODY()
public:
	UHealthWidgetComponent();                                 

	virtual void SetHealthVisibility(bool) override;

protected:
	virtual void BeginPlay() override;
};
