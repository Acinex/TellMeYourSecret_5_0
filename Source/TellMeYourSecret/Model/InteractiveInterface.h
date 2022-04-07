#pragma once
#include "UObject/Interface.h"
#include "InteractiveInterface.generated.h"

UINTERFACE()
class TELLMEYOURSECRET_API UInteractiveInterface : public UInterface
{
    GENERATED_BODY()
};

class TELLMEYOURSECRET_API IInteractiveInterface
{
    GENERATED_BODY()
public:
    /** Used to animate this object to its 'on' state */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Latent, LatentInfo="LatentInfo"))
    void AnimateOn(FLatentActionInfo LatentInfo);
    /** Used to animate this object to its 'of' state */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(Latent, LatentInfo="LatentInfo"))
    void AnimateOff(FLatentActionInfo LatentInfo);
    /** Used to set this object to its 'on' state immediately */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void TurnOn();
    /** Used to set this object to its 'of' state immediately */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void TurnOff();
};
