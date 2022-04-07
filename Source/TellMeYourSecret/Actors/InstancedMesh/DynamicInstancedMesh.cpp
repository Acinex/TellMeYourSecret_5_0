#include "DynamicInstancedMesh.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

UHierarchicalInstancedStaticMeshComponent* ADynamicInstancedMesh::GetMeshComponent(UStaticMesh* Mesh)
{
    TArray<UHierarchicalInstancedStaticMeshComponent*> MeshComponents;
    GetComponents<UHierarchicalInstancedStaticMeshComponent>(MeshComponents);

    for (UHierarchicalInstancedStaticMeshComponent* Component : MeshComponents)
    {
        if (Component->GetStaticMesh() == Mesh)
        {
            return Component;
        }
    }

    Meshes.Add(Mesh);

    UHierarchicalInstancedStaticMeshComponent* MeshComponent = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
    MeshComponent->RegisterComponent();
    MeshComponent->SetStaticMesh(Mesh);
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    MeshComponent->AttachToComponent(SceneComponentRoot, AttachmentRules);

    Components = MeshComponents;
    Components.Add(MeshComponent);

    return MeshComponent;
}
