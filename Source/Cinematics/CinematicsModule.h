#pragma once
#include "Modules/ModuleInterface.h"

class ICinematicsModule : public IModuleInterface
{
public:
    static ICinematicsModule& Get()
    {
        return FModuleManager::LoadModuleChecked<ICinematicsModule>("Cinematics");
    }
    
    virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;
    
    virtual void StopInGameLoadingScreen() = 0;
};