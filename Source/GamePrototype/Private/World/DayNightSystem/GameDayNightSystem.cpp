// (c) G3RKA. Game Prototype

#include "World/DayNightSystem/GameDayNightSystem.h"
#include "Engine/DirectionalLight.h"

void AGameDayNightSystem::OnConstruction(const FTransform& InTransform)
{
	Super::OnConstruction(InTransform);
	CurrentTime = (Day - 1) * SecondsInDay + Hour * SecondsInHour + Minute * SecondsInMinute + Seconds;
	UpdateAll();
}

void AGameDayNightSystem::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ThisClass::TimeAdding, GetTimeRate(), true);
}

void AGameDayNightSystem::UpdateAll()
{
	UpdateLight();
}

void AGameDayNightSystem::UpdateLight()
{
	if (SunLight && SunCurveMovement)
	{
		float CurrentPitch = SunCurveMovement->GetFloatValue(GetCurrentHour());
		SunLight->SetActorRotation(FRotator(CurrentPitch, 0, 0));
		UE_LOG(LogTemp, Warning, TEXT("Pitch %f"), CurrentPitch);
	}
}

float AGameDayNightSystem::GetCurrentHour()
{
	return static_cast<float>(FMath::RoundToInt32(CurrentTime) % SecondsInDay) / 3600;
}

void AGameDayNightSystem::TimeAdding()
{
	CurrentTime += TimeRateMultiplier * GetTimeRate();
	UpdateAll();
}

float AGameDayNightSystem::GetTimeRate()
{
	return FMath::Max(MinimunTimeUpdate, 1 / TimeRateMultiplier);
}
