// Copyright Acinex Games 2020

#include "PlaySoundFlowNode.h"

#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "Kismet/GameplayStatics.h"

UPlaySoundFlowNode::UPlaySoundFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif
}

void UPlaySoundFlowNode::ExecuteInput(const FName& PinName)
{
	if (!Sound.IsValid())
	{
		return Finish();
	}

	if (!IdentityTags.IsValid())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Sound.Get());
	}
	else
	{
		for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::Any))
		{
			UGameplayStatics::PlaySoundAtLocation(FoundComponent.Get(), Sound.Get(), FoundComponent.Get()->GetOwner()->GetActorLocation());
		}
	}

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString UPlaySoundFlowNode::GetNodeDescription() const
{
	if (!Sound.IsValid())
	{
		return TEXT("No Sound selected");
	}

	FString Description = TEXT("Playing Sound ");

	Description.Append(Sound->GetName());

	if (IdentityTags.IsValid())
	{
		Description.Append(TEXT(" At ")).Append(IdentityTags.ToString());
	}

	return Description;
}

bool UPlaySoundFlowNode::IsParametersValid() const
{
	return Sound.IsValid();
}

#endif
