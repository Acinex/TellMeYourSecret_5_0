#include "InstancedMeshBase.h"

AInstancedMeshBase::AInstancedMeshBase()
{
    
    SceneComponentRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponentRoot"));
    RootComponent      = SceneComponentRoot;
}

UHierarchicalInstancedStaticMeshComponent* AInstancedMeshBase::GetMeshComponent(UStaticMesh* Mesh)
{
    return nullptr;
}
