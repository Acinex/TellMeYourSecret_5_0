// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Flow/ActorFlowNode.h"

#include "AttachActorFlowNode.generated.h"

UCLASS(NotBlueprintable, meta=(DisplayName="Attach Actor"))
class TELLMEYOURSECRET_API UAttachActorFlowNode : public UActorFlowNode
{
	GENERATED_BODY()
public:
	explicit UAttachActorFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	/** The socket, the object should be to attached to */
	UPROPERTY(EditAnywhere, Category=Item)
	FName SocketName;
	/** Determines how the object is attached */
	UPROPERTY(EditAnywhere, Category=Item)
	EAttachmentRule AttachmentRule = EAttachmentRule::KeepWorld;
	/** Relative Rotation to the Socket from this object */
	UPROPERTY(EditAnywhere, Category=Item, meta=(EditCondition="AttachmentRule != EAttachmentRule::KeepWorld"))
	FRotator Rotation;
	/** Relative Translate to the Socket from this object */
	UPROPERTY(EditAnywhere, Category=Item, meta=(EditCondition="AttachmentRule != EAttachmentRule::KeepWorld"))
	FVector Translate;
	UPROPERTY(EditAnywhere, Category = "Item")
	FGameplayTagContainer ItemIdentityTags;

	virtual void OnLoad_Implementation() override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

private:
	UPROPERTY(SaveGame)
	TWeakObjectPtr<AActor> AttachedItem;

	void Attach();
};
