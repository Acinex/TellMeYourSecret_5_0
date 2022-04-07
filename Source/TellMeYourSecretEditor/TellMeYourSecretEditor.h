// Copyright Acinex Games 2020.

#pragma once

#include "IAssetTypeActions.h"

class TELLMEYOURSECRETEDITOR_API FTellMeYourSecretEditor : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:	
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetActions;
	
	void RegisterAssets();
	void UnregisterAssets();
};
