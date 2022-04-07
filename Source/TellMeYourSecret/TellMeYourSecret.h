// Copyright Acinex Games 2020.

#pragma once

class FTellMeYourSecretGameModule : public FDefaultGameModuleImpl
{
public:
	// Called whenever the module is starting up. In here, we unregister any style sets 
	// (which may have been added by other modules) sharing our 
	// style set's name, then initialize our style set. 
	virtual void StartupModule() override;

	// Called whenever the module is shutting down. Here, we simply tell our MenuStyles to shut down.
	virtual void ShutdownModule() override;
};
