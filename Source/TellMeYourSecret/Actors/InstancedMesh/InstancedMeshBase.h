#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedMeshBase.generated.h"

class UStaticMesh;
class UHierarchicalInstancedStaticMeshComponent;
class UInstancedStaticMeshComponent;

UCLASS(Blueprintable, BlueprintType, Abstract)
class TELLMEYOURSECRET_API AInstancedMeshBase : public AActor
{
    GENERATED_BODY()

public:
    AInstancedMeshBase();

    UFUNCTION(BlueprintPure)
    virtual UHierarchicalInstancedStaticMeshComponent* GetMeshComponent(UStaticMesh* Mesh);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USceneComponent* SceneComponentRoot;
};
