#include "GridInstancedMesh.h"


#include "TellMeYourSecret/Log.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

AGridInstancedMesh::AGridInstancedMesh()
{
    MeshComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(SceneComponentRoot);
}

void AGridInstancedMesh::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    MeshComponent->ClearInstances();

    UStaticMesh* Mesh = MeshComponent->GetStaticMesh();
    if (!Mesh)
    {
        return;
    }

    const FVector Size = Mesh->GetBounds().GetBox().GetSize();
    for (int32 IndexX = 0; IndexX < X; IndexX++)
    {
        for (int32 IndexY = 0; IndexY < Y; IndexY++)
        {
            FVector Location;
            Location.X = IndexX * Size.X + (IndexX * SpaceX);
            Location.Y = IndexY * Size.Y + (IndexY * SpaceY);
            MeshComponent->AddInstance(FTransform(Location));
        }
    }
}

UHierarchicalInstancedStaticMeshComponent* AGridInstancedMesh::GetMeshComponent(UStaticMesh* Mesh)
{
    if (MeshComponent->GetStaticMesh() && Mesh != MeshComponent->GetStaticMesh())
    {
        UE_LOG(LogTellMeYourSecret, Error, TEXT("You were calling GetMeshComponent with a differen mesh than assigned. This is not expected and will not change the Mesh"));
        return MeshComponent;
    }

    MeshComponent->SetStaticMesh(Mesh);
    return MeshComponent;
}
