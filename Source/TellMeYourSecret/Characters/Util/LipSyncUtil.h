#pragma once
#include "Syllable.h"

class FLipSyncUtil
{
public:
	static void  CreateSyllables(const FText Text, TArray<FSyllable>& Syllables);
	static bool GetMorphTarget(const FString Syllable, FName &MorphTarget);
	static TArray<FName> GetMorphTargets();

private:
	static bool ContainsSpeechPause(const FString Text, FString& Match);
	static bool Remove(FString& CurrentText, const FString Remove);
	static void Emplace(TArray<FSyllable>& Syllables, int32 SyllablesIndex, FString Letters);
};
