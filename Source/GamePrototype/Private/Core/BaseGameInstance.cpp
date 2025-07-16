// (c) G3RKA. Game Prototype


#include "Core/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBaseGameInstance::NewGame()
{
	StartLoadingLevel(NewGameLevel);
}

void UBaseGameInstance::QuitGame(APlayerController* RequestedPlayer)
{
	UKismetSystemLibrary::QuitGame(this, RequestedPlayer, EQuitPreference::Quit, true);
}

void UBaseGameInstance::LevelLoaded()
{
	OnLevelLoadedEvent.Broadcast();
}

FOnLevelStartLoadingSignature& UBaseGameInstance::OnLevelStartLoading()
{
	return OnLevelStartLoadingEvent;
}

FOnLevelLoadedSignature& UBaseGameInstance::OnLevelLoaded()
{
	return OnLevelLoadedEvent;
}

void UBaseGameInstance::StartLoadingLevel(const TSoftObjectPtr<UWorld> InLoadingLevel)
{
	LoadingLevel = InLoadingLevel;
	OnLevelStartLoadingEvent.Broadcast();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::LoadLevel, LoadingDelay);
}

void UBaseGameInstance::LoadLevel()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LoadingLevel);
}
