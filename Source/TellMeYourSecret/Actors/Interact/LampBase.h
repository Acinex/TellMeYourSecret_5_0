// Copyright Acinex Games 2020

#pragma once
#include "StatefulInteractiveObject.h"
#include "Components/LightComponent.h"
#include "LampBase.generated.h"

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API ALampBase : public AStatefulInteractiveObject
{
    GENERATED_BODY()
public:
    ALampBase();

    virtual void OnConstruction(const FTransform& Transform) override;

    virtual void AnimateOn_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void AnimateOff_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void TurnOn_Implementation() override;
    virtual void TurnOff_Implementation() override;
    UFUNCTION(BlueprintCallable)
    virtual void SetColor(const FColor NewColor);

    FORCEINLINE void SetEmissives(const float On, const float Off)
    {
        OnEmissive  = On;
        OffEmissive = Off;
    }

    FORCEINLINE void SetIntensities(const float On, const float Off)
    {
        OnIntensity  = On;
        OffIntensity = Off;
    }

protected:
    UPROPERTY(EditAnywhere, meta=(Description="Intensity for all lights, when this lamp is on"))
    float OnIntensity = 10.0F;
    UPROPERTY(EditAnywhere, meta=(Description="Intensity for all lights, when this lamp is off"))
    float OffIntensity;
    UPROPERTY(EditAnywhere, meta=(Description="Emissive for the material, when the lamp is on"))
    float OnEmissive;
    UPROPERTY(EditAnywhere, meta=(Description="Emissive for the material, when this lamp is of"))
    float OffEmissive;
    UPROPERTY(EditAnywhere, meta=(Description="Name of the emissive value in the material"))
    FName EmissiveName = FName("EmissiveStrength");
    UPROPERTY(EditAnywhere, meta=(Description="Name of the emissive color value in the material"))
    FName EmissiveColorName = FName("EmissiveColor");
    UPROPERTY(EditAnywhere, BlueprintSetter="SetColor", meta=(Description="Color for both lights and material"))
    FColor Color = FColor::White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterialInstanceDynamic* Material;

    TSet<ULightComponent*> GetLights() const;

private:
    void TurnOn() const;
    void TurnOff() const;
};
