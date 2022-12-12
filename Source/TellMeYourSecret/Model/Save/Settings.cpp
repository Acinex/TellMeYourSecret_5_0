#include "Settings.h"

USettings* USettings::Get()
{
	return GEngine ? CastChecked<USettings>(GEngine->GetGameUserSettings()) : nullptr;
}
