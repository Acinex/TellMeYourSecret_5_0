// Copyright Acinex Games 2020


#include "ChangeWeatherFlowNode.h"

#include "FlowSubsystem.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Kismet/KismetMathLibrary.h"
#include "TellMeYourSecret/Utils/CompletablePendingLatentAction.h"

class FChangeWeatherLatentAction : public FPendingLatentAction
{
	float TimeRemaining;
	FName ExecutionFunction;
	TWeakObjectPtr<UChangeWeatherFlowNode> CallbackTarget;

public:
	FChangeWeatherLatentAction(const float Duration, const FName ExecutionFunction, TWeakObjectPtr<UChangeWeatherFlowNode> CallbackTarget)
		: TimeRemaining(Duration),
		  ExecutionFunction(ExecutionFunction),
		  CallbackTarget(CallbackTarget)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		TimeRemaining -= Response.ElapsedTime();
		CallbackTarget->Update(TimeRemaining);
		Response.FinishAndTriggerIf(TimeRemaining <= 0, ExecutionFunction, 0, FWeakObjectPtr(CallbackTarget.Get()));
	}
};

UChangeWeatherFlowNode::UChangeWeatherFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif
	OutputPins.Emplace(TEXT("Complete"));
}

void UChangeWeatherFlowNode::ExecuteInput(const FName& PinName)
{
	UpdateInitial();

	TriggerFirstOutput(false);
}

void UChangeWeatherFlowNode::OnLoad_Implementation()
{
	Update(Timing - Progress);
}

#if WITH_EDITOR
FString UChangeWeatherFlowNode::GetNodeDescription() const
{
	FString Description;
	if (Data.bChangeLayerBottomAltitude)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes LayerBottomAltitude to %f"), Data.LayerBottomAltitude));
	}
	if (Data.bChangeLayerHeight)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes LayerHeight to %f"), Data.LayerHeight));
	}
	if (Data.bChangeTemperature)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes Temperature to %f"), Data.Temperature));
	}
	if (Data.bChangeIntensity)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes Intensity to %f"), Data.Intensity));
	}
	if (Data.bChangeLightColor)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes LightColor to %s"), *Data.LightColor.ToString()));
	}
	if (Data.bChangeVolumetricFog)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes VolumetricFog to %i"), Data.bVolumetricFog));
	}
	if (Data.bChangeFogDensity)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changes FogDensity to %f"), Data.FogDensity));
	}

	return Description;
}

FString UChangeWeatherFlowNode::GetStatusString() const
{
	FString Description = FString::Printf(TEXT("Progress: %f"), Progress);
	if (Data.bChangeLayerBottomAltitude)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing LayerBottomAltitude from %f to %f"), InitialData.LayerBottomAltitude, LayerBottomAltitude));
	}
	if (Data.bChangeLayerHeight)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing LayerHeight from %f to %f"), InitialData.LayerHeight, LayerHeight));
	}
	if (Data.bChangeTemperature)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing Temperature from %f to %f"), InitialData.Temperature, Temperature));
	}
	if (Data.bChangeIntensity)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing Intensity from %f to %f"), InitialData.Intensity, Intensity));
	}
	if (Data.bChangeLightColor)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing LightColor from %s to %s"), *InitialData.LightColor.ToString(), *LightColor.ToString()));
	}
	if (Data.bChangeVolumetricFog)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing VolumetricFog from %i to %i"), InitialData.bVolumetricFog, Data.bVolumetricFog));
	}
	if (Data.bChangeFogDensity)
	{
		if (Description.Len())
		{
			Description.Append(LINE_TERMINATOR);
		}
		Description.Append(FString::Printf(TEXT("Changing FogDensity from %f to %f"), InitialData.FogDensity, FogDensity));
	}

	return Description;
}
#endif

void UChangeWeatherFlowNode::Cleanup()
{
	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();
	LatentActionManager.RemoveActionsForObject(this);
}

void UChangeWeatherFlowNode::Complete()
{
	TriggerOutput(TEXT("Complete"), true);
}

void UChangeWeatherFlowNode::UpdateInitial()
{
	static FGameplayTag CloudsGamePlayTag = FGameplayTag::RequestGameplayTag("Weather.Clouds");
	static FGameplayTag SunGamePlayTag = FGameplayTag::RequestGameplayTag("Weather.Sun");
	static FGameplayTag FogGamePlayTag = FGameplayTag::RequestGameplayTag("Weather.Fog");

	TSet<AActor*> Actors = GetFlowSubsystem()->GetFlowActorsByTag(CloudsGamePlayTag, AVolumetricCloud::StaticClass());

	for (const AActor* Actor : Actors)
	{
		const UVolumetricCloudComponent* Component = Actor->FindComponentByClass<UVolumetricCloudComponent>();

		InitialData.LayerBottomAltitude = Component->LayerBottomAltitude;
		InitialData.LayerHeight = Component->LayerHeight;
	}

	Actors = GetFlowSubsystem()->GetFlowActorsByTag(SunGamePlayTag, ADirectionalLight::StaticClass());

	for (const AActor* Actor : Actors)
	{
		const UDirectionalLightComponent* Component = Actor->FindComponentByClass<UDirectionalLightComponent>();

		InitialData.Temperature = Component->Temperature;
		InitialData.Intensity = Component->Intensity;
		InitialData.LightColor = Component->LightColor;
	}

	Actors = GetFlowSubsystem()->GetFlowActorsByTag(FogGamePlayTag, AExponentialHeightFog::StaticClass());

	for (const AActor* Actor : Actors)
	{
		const UExponentialHeightFogComponent* Component = Actor->FindComponentByClass<UExponentialHeightFogComponent>();
		InitialData.bVolumetricFog = Component->bEnableVolumetricFog;
		InitialData.FogDensity = Component->FogDensity;
	}

	if (Progress < Timing)
	{
		FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();
		FChangeWeatherLatentAction* Action = new FChangeWeatherLatentAction(Timing, TEXT("Complete"), this);
		LatentActionManager.AddNewAction(this, rand(), Action);
	}
}

void UChangeWeatherFlowNode::Update(const float TimeRemaining)
{
	Progress = FMath::Min(1, (Timing - TimeRemaining) / Timing);

	static FGameplayTag CloudsGamePlayTag = FGameplayTag::RequestGameplayTag("Weather.Clouds");
	static FGameplayTag SunGamePlayTag = FGameplayTag::RequestGameplayTag("Weather.Sun");
	static FGameplayTag FogGamePlayTag = FGameplayTag::RequestGameplayTag("Weather.Fog");

	if (Data.bChangeLayerBottomAltitude || Data.bChangeLayerHeight)
	{
		TSet<AActor*> Actors = GetFlowSubsystem()->GetFlowActorsByTag(CloudsGamePlayTag, AVolumetricCloud::StaticClass());

		UE_LOG(LogTemp, Warning, TEXT("%i Actors matching the Clouds"), Actors.Num())

		for (const AActor* Actor : Actors)
		{
			UVolumetricCloudComponent* Component = Actor->FindComponentByClass<UVolumetricCloudComponent>();
			if (Data.bChangeLayerBottomAltitude)
			{
				LayerBottomAltitude = FMath::Lerp(InitialData.LayerBottomAltitude, Data.LayerBottomAltitude, Progress);
				Component->SetLayerBottomAltitude(LayerBottomAltitude);
			}
			if (Data.bChangeLayerHeight)
			{
				LayerHeight = FMath::Lerp(InitialData.LayerHeight, Data.LayerHeight, Progress);
				Component->SetLayerHeight(FMath::Lerp(InitialData.LayerHeight, Data.LayerHeight, Progress));
			}
		}
	}

	if (Data.bChangeTemperature || Data.bChangeIntensity || Data.bChangeLightColor)
	{
		TSet<AActor*> Actors = GetFlowSubsystem()->GetFlowActorsByTag(SunGamePlayTag, ADirectionalLight::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("%i Actors matching the Sun"), Actors.Num())

		for (const AActor* Actor : Actors)
		{
			UDirectionalLightComponent* Component = Actor->FindComponentByClass<UDirectionalLightComponent>();
			if (Data.bChangeTemperature)
			{
				Temperature = FMath::Lerp(InitialData.Temperature, Data.Temperature, Progress);
				Component->SetTemperature(Temperature);
			}
			if (Data.bChangeIntensity)
			{
				Intensity = FMath::Lerp(InitialData.Intensity, Data.Intensity, Progress);
				Component->SetIntensity(FMath::Lerp(InitialData.Intensity, Data.Intensity, Progress));
			}
			if (Data.bChangeLightColor)
			{
				LightColor = UKismetMathLibrary::LinearColorLerp(InitialData.LightColor, Data.LightColor, Progress);
				Component->SetLightColor(LightColor);
			}
		}
	}

	if (Data.bChangeVolumetricFog || Data.bChangeFogDensity)
	{
		TSet<AActor*> Actors = GetFlowSubsystem()->GetFlowActorsByTag(FogGamePlayTag, AExponentialHeightFog::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("%i Actors matching the Fog"), Actors.Num())

		for (const AActor* Actor : Actors)
		{
			UExponentialHeightFogComponent* Component = Actor->FindComponentByClass<UExponentialHeightFogComponent>();
			if (Data.bChangeVolumetricFog)
			{
				Component->SetVolumetricFog(InitialData.bVolumetricFog);
			}
			if (Data.bChangeFogDensity)
			{
				FogDensity = FMath::Lerp(InitialData.FogDensity, Data.FogDensity, Progress);
				Component->SetFogDensity(FogDensity);
			}
		}
	}
}
