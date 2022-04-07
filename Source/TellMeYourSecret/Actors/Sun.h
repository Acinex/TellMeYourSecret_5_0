#pragma once
#include "OrbitingActor.h"
#include "Sun.generated.h"

class UDirectionalLightComponent;

UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API ASun : public AOrbitingActor
{
	GENERATED_BODY()
public:
	explicit ASun(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	void SetTime(const float Time);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDirectionalLightComponent* DirectionalLight;
};
