// (c) G3RKA. Game Prototype

#include "World/Border/WorldBorder.h"
#include "Components/BoxComponent.h"

AWorldBorder::AWorldBorder() : Super()
{
	ExternalBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("External Box"));
	check(ExternalBoxCollision);
	ExternalBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnExternalAreaExit);
	SetRootComponent(ExternalBoxCollision);

	InternalBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Internal Box"));
	check(InternalBoxCollision);
	InternalBoxCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInternalAreaExit);
	InternalBoxCollision->SetupAttachment(ExternalBoxCollision);
}

void AWorldBorder::OnExternalAreaExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetActorLocation(Location);
	}
}

void AWorldBorder::OnInternalAreaExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	check(OtherActor);
	Player = OtherActor;
	Location = OtherActor->GetActorLocation();
}


