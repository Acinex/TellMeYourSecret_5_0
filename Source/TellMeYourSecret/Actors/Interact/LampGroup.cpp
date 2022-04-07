#include "LampGroup.h"

void ALampGroup::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    BoundActors.Empty();

    for (ALampBase* Lamp : Lamps)
    {
        if (!Lamp)
        {
            continue;
        }

        BoundActors.Add(Lamp);

        if (bPropagateEmissive)
        {
            Lamp->SetEmissives(OnEmissive, OffEmissive);
        }

        if (bPropagateIntensity)
        {
            Lamp->SetIntensities(OnIntensity, OffIntensity);
        }
    }
}

void ALampGroup::SetColor(const FColor NewColor)
{
    Super::SetColor(NewColor);
    if (!bPropagateColor)
    {
        return;
    }

    for (ALampBase* Lamp : Lamps)
    {
        if (Lamp)
        {
            Lamp->SetColor(NewColor);
        }
    }
}
