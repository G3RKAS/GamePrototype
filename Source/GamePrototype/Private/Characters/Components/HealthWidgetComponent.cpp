// (c) G3RKA. Game Prototype


#include "Characters/Components/HealthWidgetComponent.h"
#include "Interfaces/Characters/HealthWidgetInterface.h"

UHealthWidgetComponent::UHealthWidgetComponent() : Super()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(175, 10));
	SetVisibility(false);
}

void UHealthWidgetComponent::SetHealthVisibility(bool InVisibility)
{
	SetVisibility(InVisibility);
}

void UHealthWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	check(GetWidget());
	IHealthWidgetInterface* WidgetInteraction = Cast<IHealthWidgetInterface>(GetWidget());
	WidgetInteraction->SetBindType(GetOwner());
}
