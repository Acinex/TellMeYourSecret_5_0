// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Flow/ActorFlowNode.h"

#include "NonPlayerComponentFlowNode.generated.h"

class UCharacterComponent;
class UNonPlayerComponent;
class UFlowComponent;

UCLASS(Abstract, NotBlueprintable)
class TELLMEYOURSECRET_API UNonPlayerComponentFlowNode : public UActorFlowNode
{
	GENERATED_BODY()
public:
	explicit UNonPlayerComponentFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	TWeakObjectPtr<UNonPlayerComponent> FindNonPlayer() const;
	TWeakObjectPtr<UCharacterComponent> FindCharacter() const;

private:
	template <class T>
	TWeakObjectPtr<T> FindComponent() const;
};
