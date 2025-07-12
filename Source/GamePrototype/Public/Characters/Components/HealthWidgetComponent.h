// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthWidgetComponent.generated.h"

UCLASS()
class GAMEPROTOTYPE_API UHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UHealthWidgetComponent();                                 

	virtual void SetHealthVisibility(bool);

protected:
	virtual void BeginPlay() override;
};
