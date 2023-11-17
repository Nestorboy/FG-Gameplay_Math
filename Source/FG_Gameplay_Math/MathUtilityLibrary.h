#pragma once

#include "CoreMinimal.h"

#include "MathUtilityLibrary.generated.h"

UCLASS()
class FG_GAMEPLAY_MATH_API UMathUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Math Utility")
	static float AngleRadians(const FVector& From, const FVector& To)
	{
		const float Scalar = From.Dot(To);
		return FMath::Acos(Scalar);
	}

	UFUNCTION(BlueprintCallable, Category = "Math Utility")
	static float AngleDegrees(const FVector& From, const FVector& To)
	{
		return FMath::RadiansToDegrees(AngleRadians(From, To));
	}
};
