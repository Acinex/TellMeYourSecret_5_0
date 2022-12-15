// Copyright Acinex Games 2020.

using UnrealBuildTool;

public class TellMeYourSecret : ModuleRules
{
	public TellMeYourSecret(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseUnity = false;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"DeveloperSettings",
			"Flow",
			"PhysicsCore",
			"AnimGraphRuntime"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"GameplayTags",
			"MoviePlayer",
			"Cinematics",
			"Slate",
			"SlateCore",
			"Niagara",
			"AudioModulation", "CommonUI"
		});
	}
}