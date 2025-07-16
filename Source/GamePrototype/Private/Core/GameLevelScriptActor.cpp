// (c) G3RKA. Game Prototype


#include "Core/GameLevelScriptActor.h"
#include "Interfaces/Game/GameControl.h"

void AGameLevelScriptActor::BeginPlay()
{
	GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ThisClass::DelayLoadLevel));
}

void AGameLevelScriptActor::DelayLoadLevel()
{
	IGameControl* GameControl = GetGameInstance<IGameControl>();
	check(GameControl);
	GameControl->LevelLoaded();
}
