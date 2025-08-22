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

	check(Clouds);
	UVolumetricCloudComponent* CloudComponent = GetCloudComponent();
	check(CloudComponent);

	UMaterialInstanceDynamic* NewMaterial =
		UMaterialInstanceDynamic::Create(CloudComponent->GetMaterial(), CloudComponent);

	CloudComponent->SetMaterial(NewMaterial);
	CloudMaterial = NewMaterial;

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
			if (GetWorld()->IsGameWorld())
			{
				UE_LOG(LogTemp, Warning, TEXT("Not Editor"));
				ChangeCloudCoverageBasedOnIntensity(SunIntensity);
			}
			else
			{
			#if WITH_EDITOR
				ChangeCloudCoverageBasedOnIntensityInEditor(SunIntensity);
			#endif
			}
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

#if WITH_EDITOR
void AGameDayNightSystem::ChangeCloudCoverageBasedOnIntensityInEditor(float InIntensity)
{
	UMaterialInstanceConstant* MatInst = Cast<UMaterialInstanceConstant>(GetCloudComponent()->GetMaterial());

	if (MatInst)
	{
		UE_LOG(LogTemp, Warning, TEXT("Coverage %f"), GetCloudCoverageBasedOnIntensity(InIntensity));
		MatInst->SetScalarParameterValueEditorOnly(TEXT("Cloud_GlobalCoverage"),
												   GetCloudCoverageBasedOnIntensity(InIntensity));
	}
}
#endif

void AGameDayNightSystem::ChangeCloudCoverageBasedOnIntensity(float InIntensity)
{
	if (Clouds)
	{
		UE_LOG(LogTemp, Warning, TEXT("Coverage %f"), GetCloudCoverageBasedOnIntensity(InIntensity));
		CloudMaterial->SetScalarParameterValue(TEXT("Cloud_GlobalCoverage"), GetCloudCoverageBasedOnIntensity(InIntensity));
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
