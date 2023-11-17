#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demonstrator.generated.h"

UCLASS(hidecategories=(Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class FG_GAMEPLAY_MATH_API ADemonstrator : public AActor
{
	GENERATED_BODY()

public:
	ADemonstrator();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	UStaticMeshComponent* StaticMeshComponent;
};
