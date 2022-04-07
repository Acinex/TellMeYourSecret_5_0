#pragma once
#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "AbstractReputationCheckFlowNode.generated.h"

UCLASS(Abstract)
class TELLMEYOURSECRET_API UAbstractReputationCheckFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()

public:
	explicit UAbstractReputationCheckFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual bool GetDynamicTitleColor(FLinearColor& OutColor) const override { return false; }
	virtual FString GetStatusString() const override;
#endif

protected:
	virtual bool Check(const TWeakObjectPtr<UNonPlayerComponent, FWeakObjectPtr>& NonPlayerComponent) const;

private:
	TWeakObjectPtr<UNonPlayerComponent> CachedNonPlayerComponent;
};
