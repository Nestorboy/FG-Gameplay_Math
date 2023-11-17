#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntersectionLibrary.generated.h"

UCLASS()
class FG_GAMEPLAY_MATH_API UIntersectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// Point,
	// Sphere,
	// Plane,
	// AABB,
	// Ray,
public:
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool PointSphere(
		const FVector& Point,
		const FVector& SphereCenter, const float SphereRadius,
		FVector& ContactPoint)
	{
		const FVector Diff = Point - SphereCenter;
		const bool IsIntersecting = Diff.SquaredLength() <= SphereRadius * SphereRadius;

		if (IsIntersecting)
		{
			ContactPoint = Diff.GetSafeNormal() * SphereRadius;
		}
		
		return IsIntersecting;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool PointPlane(
		const FVector& Point,
		const FVector& PlaneCenter, const FVector& PlaneNormal,
		FVector& ContactPoint)
	{
		const float DistanceToPlane = Point.Dot(PlaneNormal) - PlaneCenter.Dot(PlaneNormal);
		const bool IsIntersecting = DistanceToPlane <= 0.0f;

		if (IsIntersecting)
		{
			ContactPoint = Point - PlaneNormal * FMath::Sqrt(DistanceToPlane);
		}
		
		return IsIntersecting;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool PointAABB(
		const FVector& Point,
		const FVector& AABBMin, const FVector& AABBMax
		//, FVector& ContactPoint
		)
	{
		const bool IsIntersecting =
			Point.X < AABBMin.X || Point.X > AABBMax.X ||
			Point.Y < AABBMin.Y || Point.Y > AABBMax.Y ||
			Point.Z < AABBMin.Z || Point.Z > AABBMax.Z;

		//if (IsIntersecting)
		//{
		//	
		//}
		
		return IsIntersecting;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereSphere(const FVector& P1, const float R1, const FVector& P2, const float R2, FVector& ContactPoint)
	{
		const float RadiusSum = R1 + R2;
		const FVector Diff = P1 - P2;
		const bool IsIntersecting = Diff.SquaredLength() <= RadiusSum * RadiusSum;

		if (IsIntersecting)
		{
			ContactPoint = Diff.GetSafeNormal() * R2;
		}
		
		return IsIntersecting;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SpherePlane(
		const FVector& SphereCenter, const float SphereRadius,
		const FVector& PlaneCenter, const FVector& PlaneNormal,
		FVector& ContactPoint)
	{
		const float DistanceToPlane = SphereCenter.Dot(PlaneNormal) - PlaneCenter.Dot(PlaneNormal);
		const bool IsIntersecting = DistanceToPlane <= SphereRadius * SphereRadius;

		if (IsIntersecting)
		{
			ContactPoint = SphereCenter - PlaneNormal * FMath::Sqrt(DistanceToPlane);
		}
		
		return IsIntersecting;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereAABB(
		const FVector& SphereCenter, const float SphereRadius,
		const FVector& AABBMin, const FVector& AABBMax
		//, FVector& ContactPoint
		)
	{
		const FVector ClosestOnAABB = ClampVector(SphereCenter, AABBMin, AABBMax);
		const FVector Diff = SphereCenter - ClosestOnAABB;

		const float DistanceToAABB = Diff.SquaredLength();
		const bool IsIntersecting = DistanceToAABB <= SphereRadius * SphereRadius;

		//if (IsIntersecting)
		//{
		//	
		//}
		
		return IsIntersecting;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereRay(
		const FVector& SphereCenter, const float SphereRadius,
		const FVector& RayOrigin, const FVector& RayDirection,
		FVector& ContactPoint)
	{
		const float DistanceAlongRay = SphereCenter.Dot(RayDirection) - RayOrigin.Dot(RayDirection);

		// Ignore if sphere is too far behind ray
		if (DistanceAlongRay + SphereRadius < 0.0f)
		{
			return false;
		}

		const FVector RayPlane = RayOrigin + RayDirection * DistanceAlongRay;
		const float DistanceToSphere = (SphereCenter - RayPlane).SquaredLength();
		const bool IsIntersecting = DistanceToSphere <= SphereRadius * SphereRadius;
		if (IsIntersecting)
		{
			const float NormalizedDst = DistanceToSphere / (SphereRadius * SphereRadius);
			const float Offset = SphereRadius * FMath::Max(0.0f, FMath::Sqrt(1.0f - NormalizedDst));
			ContactPoint = RayOrigin + RayDirection * (DistanceAlongRay - Offset);
		}
		
		return IsIntersecting;
	}
};
