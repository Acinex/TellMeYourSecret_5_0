#include "CompletablePendingLatentAction.h"

FCompletablePendingLatentAction::FCompletablePendingLatentAction(const FLatentActionInfo& LatentInfo):
	ExecutionFunction(LatentInfo.ExecutionFunction)
  , LinkID(LatentInfo.Linkage)
  , CallbackTarget(LatentInfo.CallbackTarget)
{
}

void FCompletablePendingLatentAction::UpdateOperation(FLatentResponse& Response)
{
	Response.FinishAndTriggerIf(bCompleted, ExecutionFunction, LinkID, CallbackTarget);
}
