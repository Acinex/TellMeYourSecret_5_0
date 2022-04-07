// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "TellMeYourSecret/Flow/SpawnParams.h"

#include "SpawnComponent.generated.h"

UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API USpawnComponent : public UArrowComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	explicit USpawnComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	bool GetTransform(FTransform& Transform) const;
	void TransformActor(const FTransform Transform) const;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool Spawn(FSpawnParams& SpawnParams);
	void Despawn();

private:
	TWeakObjectPtr<AActor> SpawnedActor;
};
