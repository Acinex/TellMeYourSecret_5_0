// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "StatusReportFlowNode.h"
#include "ChangeWeatherFlowNode.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UChangeWeatherFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()

public:
	explicit UChangeWeatherFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif


protected:
	UPROPERTY(EditAnywhere, Category=Clouds)
	bool bChangeLayerBottomAltitude = false;
	UPROPERTY(EditAnywhere, Category=Clouds, meta=(EditCondition="bChangeLayerBottomAltitude"))
	float LayerBottomAltitude = 5.0F;
	
	UPROPERTY(EditAnywhere, Category=Clouds)
	bool bChangeLayerHeight = false;
	UPROPERTY(EditAnywhere, Category=Clouds, meta=(EditCondition="bChangeLayerHeight"))
	float LayerHeight = 10.0F;
	
	UPROPERTY(EditAnywhere, Category=Sun)
	bool bChangeTemperature = false;
	UPROPERTY(EditAnywhere, Category=Sun, meta=(EditCondition="bChangeTemperature"))
	float Temperature = 6500.0F;
	
	UPROPERTY(EditAnywhere, Category=Sun)
	bool bChangeIntensity = false;
	UPROPERTY(EditAnywhere, Category=Sun, meta=(EditCondition="bChangeIntensity"))
	float Intensity = 10.0F;
	
	UPROPERTY(EditAnywhere, Category=Sun)
	bool bChangeLightColor = false;
	UPROPERTY(EditAnywhere, Category=Sun, meta=(EditCondition="bChangeLightColor"))
	FColor LightColor = FColor::White;
};
