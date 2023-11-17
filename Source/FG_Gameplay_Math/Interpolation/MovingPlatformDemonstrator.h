#pragma once

#include "CoreMinimal.h"
#include "FG_Gameplay_Math/Demonstrator.h"
#include "MovingPlatformDemonstrator.generated.h"

UCLASS()
class FG_GAMEPLAY_MATH_API AMovingPlatformDemonstrator : public ADemonstrator
{
	GENERATED_BODY()

	FVector Origin;
	FVector Goal;

	FTimerHandle TravelTimer;
	FTimerHandle RestTimer;

	bool Reverse = true;
	float TValue;
	
public:
	AMovingPlatformDemonstrator();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0))
	float TravelDuration = 3.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0))
    float RestDuration = 3.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* InterpolationCurve;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (MakeEditWidget = true))
	FVector TargetPosition;
	
	virtual void BeginPlay() override;

	virtual void BeginTravelling();
	virtual void BeginResting();
	
	virtual void OnTravelFinish();
	virtual void OnRestFinish();

public:
	virtual void Tick(float DeltaTime) override;
};
