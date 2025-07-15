// (c) G3RKA. Game Prototype


#include "Core/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBaseGameInstance::NewGame()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, NewGameLevel);
}

void UBaseGameInstance::QuitGame(APlayerController* RequestedPlayer)
{
	UKismetSystemLibrary::QuitGame(this, RequestedPlayer, EQuitPreference::Quit, true);
}
