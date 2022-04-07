#pragma once
#include "LatentActions.h"

class FCompletablePendingLatentAction : public FPendingLatentAction
{

public:
	explicit FCompletablePendingLatentAction( const FLatentActionInfo& LatentInfo);
	void     Complete() { bCompleted = true; }

protected:
	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	bool           bCompleted = false;
	FName          ExecutionFunction;
	int32          LinkID = 0;
	FWeakObjectPtr CallbackTarget;
};
