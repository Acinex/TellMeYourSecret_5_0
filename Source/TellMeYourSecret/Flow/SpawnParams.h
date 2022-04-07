#pragma once
#include "BehaviorTree/BehaviorTree.h"

#include "SpawnParams.generated.h"

USTRUCT()
struct FSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ActorScale;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	bool bNoCollisionFail;

	FSpawnParams()
		: ActorScale(1.0f), bNoCollisionFail(true)
	{
	}
};
