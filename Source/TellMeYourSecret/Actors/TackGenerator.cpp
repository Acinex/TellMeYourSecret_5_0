// Copyright Acinex Games 2020

#include "TackGenerator.h"

#include "Components/TextRenderComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ATackGenerator::ATackGenerator()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    Spline->SetMobility(EComponentMobility::Static);
}

void ATackGenerator::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    const int32 NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();
    while (TrackData.Num() != NumberOfSplinePoints)
    {
        if (TrackData.Num() < NumberOfSplinePoints)
        {
            TrackData.Add(FTrackData());
        }
        else
        {
            TrackData.RemoveAt(TrackData.Num() - 1);
        }
    }

    for (int32 Index = 0; Index < NumberOfSplinePoints - (Spline->IsClosedLoop() ? 0 : 1); Index++)
    {
        BuildTrackElement(Index, RoadMesh);
    }
}

// Called when the game starts or when spawned
void ATackGenerator::BeginPlay()
{
    Super::BeginPlay();
    TArray<USceneComponent*> ChildComponents;
    Spline->GetChildrenComponents(false, ChildComponents);

    for (USceneComponent* ChildComponent : ChildComponents)
    {
        if (UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(ChildComponent))
        {
            MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        }
    }

    TArray<UTextRenderComponent*> TextRenderComponents;
    GetComponents<UTextRenderComponent>(TextRenderComponents);

    for (UTextRenderComponent* TextRenderComponent : TextRenderComponents)
    {
        TextRenderComponent->SetVisibility(false);
    }
}

void ATackGenerator::BuildTrackElement(const int32 Index, UStaticMesh* TrackElement)
{
    FVector StartLocation;
    FVector StartTangent;
    Spline->GetLocalLocationAndTangentAtSplinePoint(Index, StartLocation, StartTangent);

    const int32 NextIndex = (Index + 1) % Spline->GetNumberOfSplinePoints();
    FVector     EndLocation;
    FVector     EndTangent;
    Spline->GetLocalLocationAndTangentAtSplinePoint(NextIndex, EndLocation, EndTangent);

    USplineMeshComponent* SplineMesh = AddSplineMesh();
    if (!SplineMesh)
    {
        return;
    }

    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
    SplineMesh->bSmoothInterpRollScale = true;
    SplineMesh->SetStaticMesh(TrackElement);
    SplineMesh->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent);

    const FVector2D StartScale(TrackData[Index].Width, TrackData[Index].Thickness);
    const FVector2D EndScale(TrackData[NextIndex].Width, TrackData[NextIndex].Thickness);

    SplineMesh->SetStartRoll(TrackData[Index].Bank);
    SplineMesh->SetEndRoll(TrackData[NextIndex].Bank);
    SplineMesh->SetStartScale(StartScale);
    SplineMesh->SetEndScale(EndScale);
    SplineMesh->SetCollisionResponseToAllChannels(ECR_Block);

    UTextRenderComponent* TextRenderComponent = AddTextRender();
    if (!TextRenderComponent)
    {
        return;
    }

    TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%d"), Index)));
    TextRenderComponent->SetRelativeLocation(FVector(StartLocation.X, StartLocation.Y, 50.0F));
    TextRenderComponent->SetWorldSize(300.0F);
}

// Called every frame
void ATackGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
