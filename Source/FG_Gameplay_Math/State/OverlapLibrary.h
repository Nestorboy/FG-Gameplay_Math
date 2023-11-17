#pragma once

#include "CoreMinimal.h"
#include "FG_Gameplay_Math/MathUtilityLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OverlapLibrary.generated.h"

UCLASS()
class FG_GAMEPLAY_MATH_API UOverlapLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Overlap")
	static bool PointSphericalSector(
		const FVector& Point,
		const FVector& SectorOrigin, const FVector& SectorDirection, const float SectorRadius, const float SectorDegrees)
	{
		const FVector ToPoint = Point - SectorOrigin;
		if (ToPoint.SquaredLength() > SectorRadius * SectorRadius)
		{
			return false;
		}
		
		const FVector ToPointDir = ToPoint.GetSafeNormal();
		const float Degrees = UMathUtilityLibrary::AngleDegrees(ToPointDir, SectorDirection);
		return Degrees <= SectorDegrees;
	}

	UFUNCTION(BlueprintCallable, Category = "Overlap")
	static bool PointPlane(
		const FVector& Point,
		const FVector& PlanePosition, const FVector& PlaneNormal)
	{
		const float DistanceToPlane = Point.Dot(PlaneNormal) - PlanePosition.Dot(PlaneNormal);
		return DistanceToPlane <= 0.0f;
	}
};
