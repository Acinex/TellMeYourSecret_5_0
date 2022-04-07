#pragma once
#include "CoreMinimal.h"
#include "InstancedMeshBase.h"
#include "DynamicInstancedMesh.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API ADynamicInstancedMesh : public AInstancedMeshBase
{
    GENERATED_BODY()

public:

    virtual UHierarchicalInstancedStaticMeshComponent* GetMeshComponent(UStaticMesh* Mesh) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UStaticMesh*> Meshes;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UHierarchicalInstancedStaticMeshComponent*> Components;
};
