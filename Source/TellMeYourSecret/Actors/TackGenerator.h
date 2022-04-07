// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TellMeYourSecret/Model/TrackData.h"

#include "TackGenerator.generated.h"

class USplineMeshComponent;
class UTextRenderComponent;
class USplineComponent;

UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API ATackGenerator : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATackGenerator();

    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    USplineComponent* Spline;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FTrackData> TrackData;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMesh* RoadMesh;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void BuildTrackElement(int32 Index, UStaticMesh* TrackElement);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    UTextRenderComponent* AddTextRender();
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    USplineMeshComponent* AddSplineMesh();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
