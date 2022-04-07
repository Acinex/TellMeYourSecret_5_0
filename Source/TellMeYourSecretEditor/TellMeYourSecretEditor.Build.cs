// Copyright Acinex Games 2020.

using UnrealBuildTool;

public class TellMeYourSecretEditor : ModuleRules
{
	public TellMeYourSecretEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseUnity = false;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.Add(System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "Source/Editor/Blutility/Private");

		PublicDependencyModuleNames.AddRange(new[] {"Core"});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"AssetTools",
			"Engine",
			"UnrealEd",
			"Slate",
			"Flow",
			"FlowEditor",
			"SlateCore",
			"Blutility",
			"UnrealEd",
			"UMG",
			"UMGEditor",
			"TellMeYourSecret",
			"GameplayTags"
		});
	}
}