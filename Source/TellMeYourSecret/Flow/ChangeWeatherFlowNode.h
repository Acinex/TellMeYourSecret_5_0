// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "ChangeWeatherFlowNode.generated.h"

USTRUCT()
struct FChangeWeatherData
{
	GENERATED_BODY()

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

	UPROPERTY(EditAnywhere, Category=Fog)
	bool bChangeVolumetricFog = false;
	UPROPERTY(EditAnywhere, Category=Fog, meta=(EditCondition="bChangeVolumetricFog"))
	bool bVolumetricFog = false;

	UPROPERTY(EditAnywhere, Category=Fog)
	bool bChangeFogDensity = false;
	UPROPERTY(EditAnywhere, Category=Fog, meta=(EditCondition="bChangeFogDensity"))
	float FogDensity = 0.020000;
};

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Change Weather"))
class TELLMEYOURSECRET_API UChangeWeatherFlowNode : public UFlowNode
{
	GENERATED_BODY()
	friend class FChangeWeatherLatentAction;

public:
	explicit UChangeWeatherFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

	virtual void OnLoad_Implementation() override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual FString GetStatusString() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category=Default)
	float Timing = 1.0F;

	UPROPERTY(EditAnywhere, meta=(ShowOnlyInnerProperties))
	FChangeWeatherData Data;

	virtual void Cleanup() override;

private:
	UPROPERTY()
	FChangeWeatherData InitialData;

	float LayerBottomAltitude = 5.0F;
	float LayerHeight = 10.0F;
	float Temperature = 6500.0F;
	float Intensity = 10.0F;
	FLinearColor LightColor = FLinearColor::White;
	bool bVolumetricFog = false;
	float FogDensity = 0.020000;

	float Progress = 0.0F;

	UFUNCTION()
	void Complete();

	void UpdateInitial();
	void Update(float TimeRemaining);
};
