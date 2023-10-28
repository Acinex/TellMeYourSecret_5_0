// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TellMeYourSecretEditorTarget : TargetRules
{
	public TellMeYourSecretEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		ExtraModuleNames.AddRange( new string[] { "TellMeYourSecret", "TellMeYourSecretEditor" } );
	}
}
