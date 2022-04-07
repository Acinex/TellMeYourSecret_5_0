#include "CoreBlueprintFunctions.h"

UWorld* UCoreBlueprintFunctions::TryGetWorld()
{
	if (GEngine)
	{
		// Get first PIE world
		// Copied from TakeUtils::GetFirstPIEWorld()
		for (const FWorldContext& Context : GEngine->GetWorldContexts())
		{
			UWorld* World = Context.World();
			if (!World || !World->IsPlayInEditor())
			{
				continue;
			}

			if (World->GetNetMode() == NM_Standalone || (World->GetNetMode() == NM_Client && Context.PIEInstance == 2))
			{
				return World;
			}
		}

		// Otherwise get the first Game World
		for (const FWorldContext& Context : GEngine->GetWorldContexts())
		{
			UWorld* World = Context.World();
			if (!World || !World->IsGameWorld())
			{
				continue;
			}

			return World;
		}
	}

	return nullptr;
}