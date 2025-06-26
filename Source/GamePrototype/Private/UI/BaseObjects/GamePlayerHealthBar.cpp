// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/GamePlayerHealthBar.h"
#include "Interfaces/Characters/HealthInteraction.h"
#include "Interfaces/Characters/LevelInteraction.h"
#include "Components/ProgressBar.h"


void UGamePlayerHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	if (GetOwningPlayerPawn())
	{
		HealthInteraction = GetOwningPlayerPawn()->FindComponentByInterface<IHealthInteraction>();
		if (HealthInteraction)
		{
			HealthInteraction->OnHealthChanged().AddUObject(this, &ThisClass::HandleHealthChanged);
			SetupHealth();
		}
		ILevelInteraction* LevelInteraction = GetOwningPlayerPawn()->FindComponentByInterface<ILevelInteraction>();
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
