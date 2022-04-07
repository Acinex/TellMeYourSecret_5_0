#include "BlueprintFunctions.h"

#include "Engine/LevelScriptActor.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Log.h"

UTellMeYourSecretGameInstance* UBlueprintFunctions::TryGetGameInstance()
{
	UWorld* World = TryGetWorld();
	if (!World)
	{
		return nullptr;
	}

	return Cast<UTellMeYourSecretGameInstance>(World->GetGameInstance());
}

TArray<FString> UBlueprintFunctions::GetStreamingLevels(const ALevelScriptActor* Level)
{
	TArray<FString> Names;

	for (const ULevelStreaming* StreamingLevel : Level->GetWorld()->GetStreamingLevels())
	{
		FString PackageName = FPackageName::GetShortName(StreamingLevel->GetWorldAssetPackageName());
		UE_LOG(LogTellMeYourSecret, Warning, TEXT("Level name: %s / %s"), *PackageName, *StreamingLevel->GetWorldAssetPackageName())
		Names.Add(StreamingLevel->GetWorldAssetPackageName());
	}
	UE_LOG(LogTellMeYourSecret, Warning, TEXT("LevelCount: %i"), Names.Num())
	return Names;
}
