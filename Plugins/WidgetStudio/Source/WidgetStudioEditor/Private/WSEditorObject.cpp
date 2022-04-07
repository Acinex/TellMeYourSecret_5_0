/* 
* Copyright (c) 2021 THEIA INTERACTIVE.  All rights reserved.
*
* Website: https://widgetstudio.design
* Documentation: https://docs.widgetstudio.design
* Support: marketplace@theia.io
* Marketplace FAQ: https://marketplacehelp.epicgames.com
*/

#include "WSEditorObject.h"
#include "WidgetStudioRuntime.h"
#include "Logging/LogMacros.h"
#include "Engine/Engine.h"
#include "WSSubsystem.h"
#include "WSSettings.h"


UWSEditorObject::UWSEditorObject()
{
}

UWSEditorObject::UWSEditorObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (GEngine)
	{
		UWidgetStudioSubsystem* WSSubsystem = GEngine->GetEngineSubsystem<UWidgetStudioSubsystem>();
		if (IsValid(WSSubsystem))
		{
			WSSubsystem->OnStyleChanged.AddDynamic(this, &UWSEditorObject::HandleStyleChanged);
		}
		else
		{
			UE_LOG(LogWidgetStudio, Warning, TEXT("Attempted to access the Widget Studio Subsystem before it exists."));
		}
	}
}

void UWSEditorObject::HandleStyleChanged()
{
	const UWidgetStudioSubsystem* WSSubsystem = GEngine->GetEngineSubsystem<UWidgetStudioSubsystem>();
	UWidgetStudioSettings* WSSettings = GetMutableDefault<UWidgetStudioSettings>();
	
	WSSettings->Theme = WSSubsystem->Theme;
	WSSettings->IconSet = WSSubsystem->IconSet;
	WSSettings->Typography = WSSubsystem->Typography;
	WSSettings->BorderRadius = WSSubsystem->BorderRadius;
	WSSettings->IdealWidth = WSSubsystem->IdealWidth;
	WSSettings->IdealHeight = WSSubsystem->IdealHeight;
}
