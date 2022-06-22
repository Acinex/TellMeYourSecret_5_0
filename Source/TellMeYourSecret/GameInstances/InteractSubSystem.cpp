// Copyright Acinex Games 2020

#include "InteractSubSystem.h"

#include "TellMeYourSecret/Actors/Interact/InteractiveObject.h"
#include "TellMeYourSecret/Quests/QuestManager.h"
#include "TellMeYourSecret/Actors/Interact/StatefulInteractiveObject.h"

class UQuestManager;

void UInteractSubSystem::Register(AInteractiveObject* Object)
{
	TWeakObjectPtr<AInteractiveObject> Pointer = TWeakObjectPtr<AInteractiveObject>(Object);

	for (const FGameplayTag& Tag : Object->IdentityTags)
	{
		if (Tag.IsValid())
		{
			Registry.Add(Tag, Pointer);
		}
	}

	InteractiveObjects.Add(Pointer);

	const int32 Index = LoadedInteractiveObjects.IndexOfByPredicate([Pointer](const FInteractiveObjectData& Item)
	{
		return Item.Name == Pointer->GetName();
	});
	if (~Index)
	{
		const FInteractiveObjectData ObjectData = LoadedInteractiveObjects[Index];
		Object->Load(ObjectData);

		LoadedInteractiveObjects.Remove(ObjectData);
	}
}

void UInteractSubSystem::Interacted(AInteractiveObject* Object, const FGameplayTagContainer Identity) const
{
	OnInteract.Broadcast(Object, Identity);
}

AInteractiveObject* UInteractSubSystem::FindObject(const FGameplayTagContainer& Identity, const EGameplayContainerMatchType MatchType) const
{
	TSet<TWeakObjectPtr<AInteractiveObject>> FoundActors;

	if (MatchType == EGameplayContainerMatchType::Any)
	{
		for (const FGameplayTag& Tag : Identity)
		{
			TArray<TWeakObjectPtr<AInteractiveObject>> ComponentsPerTag;
			Registry.MultiFind(Tag, ComponentsPerTag);
			FoundActors.Append(ComponentsPerTag);
		}
	}
	else // EGameplayContainerMatchType::All
	{
		TSet<TWeakObjectPtr<AInteractiveObject>> ActorsWithAnyTags;
		for (const FGameplayTag& Tag : Identity)
		{
			TArray<TWeakObjectPtr<AInteractiveObject>> ComponentsPerTag;
			Registry.MultiFind(Tag, ComponentsPerTag);
			ActorsWithAnyTags.Append(ComponentsPerTag);
		}

		for (const TWeakObjectPtr<AInteractiveObject>& Actor : ActorsWithAnyTags)
		{
			if (Actor.IsValid() && Actor->IdentityTags.HasAllExact(Identity))
			{
				FoundActors.Add(Actor.Get());
			}
		}
	}

	for (const TWeakObjectPtr<AInteractiveObject>& Actor : FoundActors)
	{
		if (Actor.IsValid())
		{
			return Actor.Get();
		}
	}

	return nullptr;
}

void UInteractSubSystem::Load(UTmysSaveGame* SaveGame)
{
	InteractiveObjects.Empty();
	LoadedInteractiveObjects = SaveGame->InteractiveObjects;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UInteractSubSystem::Save(UTmysSaveGame* SaveGame)
{
	TArray<FInteractiveObjectData> Values;

	for (TWeakObjectPtr<AInteractiveObject> ObjectPtr : InteractiveObjects)
	{
		if (!ObjectPtr.IsValid())
		{
			continue;
		}

		Values.Add(ObjectPtr->Save());
	}

	SaveGame->InteractiveObjects = Values;
}
