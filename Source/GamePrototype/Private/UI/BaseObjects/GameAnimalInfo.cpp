// (c) G3RKA. Game Prototype


#include "UI/BaseObjects/GameAnimalInfo.h"
#include "UI/BaseObjects/GamePlayerHealthBar.h"
#include "UI/BaseObjects/GameLevelInfo.h"

void UGameAnimalInfo::SetBindType(AActor* InActorBind)
{
	BindActor = InActorBind;
	SetupWidget();
}

void UGameAnimalInfo::SetupWidget()
{
	if (BindActor)
	{
		HealthProgressBar->SetBindType(BindActor);
		LevelInfo->SetBindType(BindActor);
	}
}
