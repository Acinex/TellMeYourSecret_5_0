#include "Sun.h"

#include "Components/DirectionalLightComponent.h"

ASun::ASun(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	DirectionalLight                             = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLight"));
	DirectionalLight->bAtmosphereSunLight  = true;
	DirectionalLight->bEnableLightShaftOcclusion = true;
}

void ASun::SetTime(const float Time)
{
	Rotate(Time);
}
