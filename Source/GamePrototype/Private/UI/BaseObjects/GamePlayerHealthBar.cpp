// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/GamePlayerHealthBar.h"
#include "Delegates/MulticastDelegateBase.h"
#include "Interfaces/Characters/HealthInteraction.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "Components/ProgressBar.h"


void UGamePlayerHealthBar::SetBindType(EBindType InBindType, AActor* InActorBind)
{
	switch (InBindType)
	{
	case EBindType::Owner:
		BindActor = GetOwningPlayerPawn();
		break;
	case EBindType::Actor:
		BindActor = InActorBind;
		break;
	}
	SetupWidget();
}

void UGamePlayerHealthBar::SetupWidget()
{
	if (BindActor)
	{
		HealthInteraction = BindActor->FindComponentByInterface<IHealthInteraction>();
		if (HealthInteraction)
		{
			HealthInteraction->OnHealthChanged().AddUObject(this, &ThisClass::HandleHealthChanged);
			SetupHealth();
		}
		ILevelInteraction* LevelInteraction = BindActor->FindComponentByInterface<ILevelInteraction>();
		if (LevelInteraction)
		{
			LevelInteraction->OnLevelUp().AddUObject(this, &ThisClass::HandleLevelUp);
		}
	}
}

void UGamePlayerHealthBar::HandleHealthChanged(float)
{
	SetupHealth();
}

void UGamePlayerHealthBar::HandleLevelUp(uint8)
{
	SetupHealth();
}

void UGamePlayerHealthBar::SetupHealth()
{
	if (HealthInteraction)
	{
		HealthProgressBar->SetPercent(HealthInteraction->GetHealthPercent());
	}
}
