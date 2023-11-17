#include "MovingPlatformDemonstrator.h"

AMovingPlatformDemonstrator::AMovingPlatformDemonstrator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatformDemonstrator::BeginPlay()
{
	Super::BeginPlay();
	Origin = GetActorLocation();
	BeginResting();
}

void AMovingPlatformDemonstrator::BeginTravelling()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TravelTimer))
	{
		return;
	}

	PrimaryActorTick.bCanEverTick = true;
	Reverse = !Reverse;
	GetWorld()->GetTimerManager().SetTimer(TravelTimer, this, &AMovingPlatformDemonstrator::OnTravelFinish, TravelDuration);
}

void AMovingPlatformDemonstrator::BeginResting()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(RestTimer))
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(RestTimer, this, &AMovingPlatformDemonstrator::OnRestFinish, RestDuration);
}

void AMovingPlatformDemonstrator::OnTravelFinish()
{
	PrimaryActorTick.bCanEverTick = false;
	BeginResting();
}

void AMovingPlatformDemonstrator::OnRestFinish()
{
	BeginTravelling();
}

void AMovingPlatformDemonstrator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Goal = Origin + TargetPosition;
	
	TValue += (Reverse ? -DeltaTime : DeltaTime) / TravelDuration;
	TValue = FMath::Clamp(TValue, 0.0f, 1.0f);

	float Value;
	if (IsValid(InterpolationCurve))
	{
		Value = InterpolationCurve->GetFloatValue(TValue);
	}
	else
	{
		Value = TValue;
	}
	const FVector NewLocation = FMath::Lerp(Origin, Goal, Value);
	SetActorLocation(NewLocation);
}

