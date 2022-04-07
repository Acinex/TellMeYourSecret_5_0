#pragma once
#include "LampBase.h"
#include "LampGroup.generated.h"

UCLASS(BlueprintType)
class ALampGroup : public ALampBase
{
    GENERATED_BODY()
public:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void SetColor(const FColor NewColor) override;
protected:
    /** Defines if this group will set the intensity of the connected lamps */
    UPROPERTY(EditAnywhere)
    bool bPropagateIntensity;
    /** Defines if this group will set the emissives of the connected lamps */
    UPROPERTY(EditAnywhere)
    bool bPropagateEmissive;
    /** Defines if this group will set the color of the connected lamps */
    UPROPERTY(EditAnywhere)
    bool bPropagateColor;

    /** Lamps are connected to this group and can be configured by this group. */
    UPROPERTY(EditInstanceOnly)
    TSet<ALampBase*> Lamps;
};
