#pragma once
#include "CoreMinimal.h"

#include "InstancedMeshBase.h"

#include "GridInstancedMesh.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
class UInstancedStaticMeshComponent;

UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API AGridInstancedMesh : public AInstancedMeshBase
{
    GENERATED_BODY()
public:
    AGridInstancedMesh();

    virtual void OnConstruction(const FTransform& Transform) override;

    virtual UHierarchicalInstancedStaticMeshComponent* GetMeshComponent(UStaticMesh* Mesh) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UHierarchicalInstancedStaticMeshComponent* MeshComponent;
    /** Amount of meshes to create along the x axis */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 X = 1;
    /** Amount of meshes to create along the y axis */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Y = 1;
    /** Distance between each mesh along the x axis */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float SpaceX = 0;
    /** Distance between each mesh along the y axis */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float SpaceY = 0;
};
