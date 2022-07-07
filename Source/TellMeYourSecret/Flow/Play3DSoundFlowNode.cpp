// Copyright Acinex Games 2020

#include "Play3DSoundFlowNode.h"

#include "Components/AudioComponent.h"

UPlay3DSoundFlowNode::UPlay3DSoundFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	InputPins.Empty();
	OutputPins.Empty();

	InputPins.Append({TEXT("Play"), TEXT("Pause"), TEXT("Stop")});
	OutputPins.Append({TEXT("Playing"), TEXT("Paused"), TEXT("Stopped")});
}

void UPlay3DSoundFlowNode::ExecuteInput(const FName& PinName)
{
	const AActor* Actor = FindActor();
	if (!Actor)
	{
		return Finish();
	}

	UAudioComponent* AudioComponent = Actor->FindComponentByClass<UAudioComponent>();

	if (PinName.IsEqual(TEXT("Play")))
	{
		if (AudioComponent->bIsPaused)
		{
			AudioComponent->SetPaused(false);
		}
		else
		{
			AudioComponent->SetSound(Sound.LoadSynchronous());
			AudioComponent->Play();
		}
		TriggerOutput(TEXT("Playing"), false);
	}
	else if (PinName.IsEqual(TEXT("Pause")))
	{
		AudioComponent->SetPaused(true);
		TriggerOutput(TEXT("Paused"), false);
	}
	else
	{
		AudioComponent->Stop();
		TriggerOutput(TEXT("Stopped"), true);
	}
}

#if WITH_EDITOR
FString UPlay3DSoundFlowNode::GetNodeDescription() const
{
	if (Sound.IsNull())
	{
		return TEXT("No Sound selected");
	}

	if (!IdentityTags.IsValid())
	{
		return TEXT("No Audio Component selected");
	}

	return Super::GetNodeDescription() + LINE_TERMINATOR + TEXT("Playing Sound ") + Sound.GetAssetName() + TEXT(" At ") + GetIdentityTagsDescription(IdentityTags);
}

bool UPlay3DSoundFlowNode::IsParametersValid() const
{
	return !Sound.IsNull() && IdentityTags.IsValid();
}

UObject* UPlay3DSoundFlowNode::GetAssetToEdit()
{
	return Sound.LoadSynchronous();
}
#endif

void UPlay3DSoundFlowNode::PreloadContent()
{
	if(!Sound.IsNull())
	{
		// ReSharper disable once CppExpressionWithoutSideEffects
		Sound.LoadSynchronous();
	}
}
