// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"
#include "World/GameWorldObject.h"
#include "GameDayNightSystem.generated.h"

class ADirectionalLight;

UCLASS()
class GAMEPROTOTYPE_API AGameDayNightSystem final : public AGameWorldObject
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform&) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Settings|Objects|Sun");
	ADirectionalLight* SunLight;

	UPROPERTY(EditInstanceOnly, Category = "Settings|Objects|Sun");
	UCurveFloat* SunCurveMovement;

	UPROPERTY(EditInstanceOnly, Category = "Settings|Date", meta = (UIMin = 0, ClampMin = 0));
	uint32 Day = 0;

	UPROPERTY(EditInstanceOnly, Category = "Settings|Date",
			  meta = (UIMin = 0, ClampMin = 0, UIMax = 23, ClampMax = 23));
	uint8 Hour = 0;

	UPROPERTY(EditInstanceOnly, Category = "Settings|Date",
			  meta = (UIMin = 0, ClampMin = 0, UIMax = 59, ClampMax = 59));
	uint8 Minute = 0;

	UPROPERTY(EditInstanceOnly, Category = "Settings|Date",
			  meta = (UIMin = 0, ClampMin = 0, UIMax = 59, ClampMax = 59));
	uint8 Seconds = 0;

	UPROPERTY(EditInstanceOnly, Category = "Settings|TimeRate", meta = (UIMin = 0.01, ClampMin = 0.01));
	float TimeRateMultiplier = 1.0f;

	UPROPERTY(EditInstanceOnly, Category = "Settings|TimeRate", meta = (UIMin = 0.05, ClampMin = 0.05));
	float MinimunTimeUpdate = 0.1f;

	UPROPERTY()
	float CurrentTime = 0.0f;

	int SecondsInDay = 86400;
	int SecondsInHour = 3600;
	int SecondsInMinute = 60;

	FTimerHandle TimeHandle;

	void UpdateAll();
	void UpdateLight();
	
	float GetCurrentHour();

	void TimeAdding();
	float GetTimeRate();
};
