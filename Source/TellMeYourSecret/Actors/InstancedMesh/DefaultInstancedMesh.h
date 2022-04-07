#pragma once
#include "CoreMinimal.h"
#include "InstancedMeshBase.h"
#include "DefaultInstancedMesh.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API ADefaultInstancedMesh : public AInstancedMeshBase
{
    GENERATED_BODY()

public:
    ADefaultInstancedMesh();

    virtual UHierarchicalInstancedStaticMeshComponent* GetMeshComponent(UStaticMesh* Mesh) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UHierarchicalInstancedStaticMeshComponent* MeshComponent;
};
