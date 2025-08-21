// (c) G3RKA. Game Prototype

#include "World/DayNightSystem/GameDayNightSystem.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

void AGameDayNightSystem::OnConstruction(const FTransform& InTransform)
{
	Super::OnConstruction(InTransform);
	CurrentTime = Day * SecondsInDay + Hour * SecondsInHour + Minute * SecondsInMinute + Seconds;
	UpdateAll();
	CheckNewDay(Day);
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

void AGameDayNightSystem::CheckNewDay(uint32 InNewDay)
{
	if (InNewDay != OldDay)
	{
		OldDay = InNewDay;
		ChangeLightIntensity();
	}
}

void AGameDayNightSystem::ChangeLightIntensity()
{
	if (SunLight)
	{
		SunLight->GetLightComponent()->SetIntensity(FMath::FRandRange(MinIntensity, MaxIntensity));
	}
}

float AGameDayNightSystem::GetCurrentHour()
{
	return static_cast<float>(FMath::RoundToInt32(CurrentTime) % SecondsInDay) / 3600;
}

uint32 AGameDayNightSystem::GetCurrentDay()
{
	return FMath::RoundToInt32(CurrentTime) / SecondsInDay;
}

void AGameDayNightSystem::TimeAdding()
{
	CurrentTime += TimeRateMultiplier * GetTimeRate();
	UpdateAll();
	CheckNewDay(GetCurrentDay());
}

float AGameDayNightSystem::GetTimeRate()
{
	return FMath::Max(MinimunTimeUpdate, 1 / TimeRateMultiplier);
}
