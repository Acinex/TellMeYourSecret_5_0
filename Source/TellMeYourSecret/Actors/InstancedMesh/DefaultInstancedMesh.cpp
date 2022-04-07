#include "DefaultInstancedMesh.h"


#include "TellMeYourSecret/Log.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

ADefaultInstancedMesh::ADefaultInstancedMesh()
{
    MeshComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(SceneComponentRoot);
}

UHierarchicalInstancedStaticMeshComponent* ADefaultInstancedMesh::GetMeshComponent(UStaticMesh* Mesh)
{
    if (MeshComponent->GetStaticMesh() && Mesh != MeshComponent->GetStaticMesh())
    {
        UE_LOG(LogTellMeYourSecret, Error, TEXT("You were calling GetMeshComponent with a differen mesh than assigned. This is not expected and will not change the Mesh"));
        return MeshComponent;
    }

    MeshComponent->SetStaticMesh(Mesh);
    return MeshComponent;
}
