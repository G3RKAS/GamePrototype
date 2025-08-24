// (c) G3RKA. Game Prototype

#include "World/DayNightSystem/GameDayNightSystem.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/VolumetricCloudComponent.h"

#include "Materials/MaterialInstanceConstant.h"

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

	check(SunLight);
	ChangeCloudCoverageBasedOnIntensity(SunLight->GetLightComponent()->Intensity);
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
	}
}

void AGameDayNightSystem::CheckNewDay(uint32 InNewDay)
{
	if (InNewDay != OldDay)
	{
		OldDay = InNewDay;
		ChangeLightIntensity();
		if (SunLight)
		{
			float SunIntensity = SunLight->GetLightComponent()->Intensity;
			ChangeCloudCoverageBasedOnIntensity(SunIntensity);
		}
	}
}

void AGameDayNightSystem::ChangeLightIntensity()
{
	if (SunLight)
	{
		SunLight->GetLightComponent()->SetIntensity(FMath::FRandRange(MinIntensity, MaxIntensity));
	}
}

void AGameDayNightSystem::ChangeCloudCoverageBasedOnIntensity(float InIntensity)
{
	if (Clouds)
	{
		UMaterialInterface* MaterialInterface = GetCloudComponent()->GetMaterial();
		if (MaterialInterface)
		{
			UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(MaterialInterface);
			if (!DynamicMaterial)
			{
				UMaterialInstanceDynamic* NewDynamicMaterial = UMaterialInstanceDynamic::Create(MaterialInterface, this);
				GetCloudComponent()->SetMaterial(NewDynamicMaterial);
				DynamicMaterial = NewDynamicMaterial;
			}
			DynamicMaterial->SetScalarParameterValue(TEXT("Cloud_GlobalCoverage"),
													 GetCloudCoverageBasedOnIntensity(InIntensity));
		}
	}
}

float AGameDayNightSystem::GetCloudCoverageBasedOnIntensity(float InIntensity)
{
	float Normalized = FMath::GetRangePct(MinIntensity, MaxIntensity, InIntensity);
	UE_LOG(LogTemp, Warning, TEXT("InIntensity %f"), InIntensity);

	return FMath::Lerp(MinCloudCoverage, MaxCloudCoverage, 1 - Normalized);
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

UVolumetricCloudComponent* AGameDayNightSystem::GetCloudComponent()
{
	return Clouds->FindComponentByClass<UVolumetricCloudComponent>();
}
