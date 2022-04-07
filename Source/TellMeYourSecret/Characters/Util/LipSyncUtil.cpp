// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#include "LipSyncUtil.h"

#include "TellMeYourSecret/Log.h"

static const FString SpeechPauseRegex = TEXT("^([\\!,.?-])");
static const FName   SHMorphTarget    = TEXT("head__eCTRLvSH");
static const FName   THMorphTarget    = TEXT("head__eCTRLvTH");
static const FName   AAMorphTarget    = TEXT("head__eCTRLvAA");
static const FName   EHMorphTarget    = TEXT("head__eCTRLvEH");
static const FName   IHMorphTarget    = TEXT("head__eCTRLvIH");
static const FName   KMorphTarget     = TEXT("head__eCTRLvK");
static const FName   LMorphTarget     = TEXT("head__eCTRLvL");
static const FName   MMorphTarget     = TEXT("head__eCTRLvM");
static const FName   OWMorphTarget    = TEXT("head__eCTRLvOW");
static const FName   SMorphTarget     = TEXT("head__eCTRLvS");
static const FName   TMorphTarget     = TEXT("head__eCTRLvT");
static const FName   UWMorphTarget    = TEXT("head__eCTRLvUW");
static const FName   WMorphTarget     = TEXT("head__eCTRLvW");
static const FName   YMorphTarget     = TEXT("head__eCTRLvY");

static TArray<FName> MorphTargets = {
	SHMorphTarget, THMorphTarget, AAMorphTarget, EHMorphTarget, IHMorphTarget, KMorphTarget, LMorphTarget, MMorphTarget, OWMorphTarget, SMorphTarget, TMorphTarget, UWMorphTarget, WMorphTarget, YMorphTarget
};

static const TMap<FString, FName> LipSyncMap = {
	{TEXT("sh"), SHMorphTarget},
	{TEXT("th"), THMorphTarget},
	{TEXT("a"), AAMorphTarget},
	{TEXT("b"), SHMorphTarget},
	{TEXT("c"), EHMorphTarget},
	{TEXT("d"), EHMorphTarget},
	{TEXT("e"), EHMorphTarget},
	{TEXT("f"), SHMorphTarget},
	{TEXT("g"), EHMorphTarget},
	{TEXT("h"), IHMorphTarget},
	{TEXT("i"), IHMorphTarget},
	{TEXT("j"), SHMorphTarget},
	{TEXT("k"), KMorphTarget},
	{TEXT("l"), LMorphTarget},
	{TEXT("m"), MMorphTarget},
	{TEXT("n"), LMorphTarget},
	{TEXT("o"), OWMorphTarget},
	{TEXT("p"), EHMorphTarget},
	{TEXT("q"), KMorphTarget},
	{TEXT("r"), AAMorphTarget},
	{TEXT("s"), SMorphTarget},
	{TEXT("t"), TMorphTarget},
	{TEXT("u"), UWMorphTarget},
	{TEXT("v"), UWMorphTarget},
	{TEXT("w"), WMorphTarget},
	{TEXT("x"), KMorphTarget},
	{TEXT("y"), YMorphTarget},
	{TEXT("z"), SMorphTarget}
};

void FLipSyncUtil::CreateSyllables(const FText Text, TArray<FSyllable>& Syllables)
{
	int32 Index = 0;

	FString CurrentText = Text.ToString().ToLower();

	while (CurrentText.Len())
	{
		if (CurrentText.TrimStart() != CurrentText)
		{
			UE_LOG(LogTellMeYourSecret, Log, TEXT("Found Space"))
			if (!Remove(CurrentText, " "))
			{
				return;
			}

			continue;
		}

		FString SpeechPauseMatch;
		if (ContainsSpeechPause(CurrentText, SpeechPauseMatch))
		{
			UE_LOG(LogTellMeYourSecret, Log, TEXT("Found pause"))
			if (!Remove(CurrentText, SpeechPauseMatch))
			{
				return;
			}

			/* Don't add as last entry */
			if (CurrentText.Len())
			{
				Emplace(Syllables, Index, TEXT(" "));
				Index++;
			}
			continue;
		}

		bool bFound = false;
		for (auto SyncMap : LipSyncMap)
		{
			const FRegexPattern Pattern(FString(TEXT("^(")).Append(SyncMap.Key).Append(")"));
			FRegexMatcher       Matcher(Pattern, CurrentText);

			if (!Matcher.FindNext())
			{
				continue;
			}

			const FString Letters = Matcher.GetCaptureGroup(0);
			UE_LOG(LogTellMeYourSecret, Log, TEXT("Found Letters: %s"), *Letters)

			if (!Remove(CurrentText, Letters))
			{
				return;
			}

			Emplace(Syllables, Index, Letters);

			Index++;
			bFound = true;
			break;
		}

		if (!bFound)
		{
			UE_LOG(LogTellMeYourSecret, Warning, TEXT("Skipped %s"), *CurrentText.Left(1))
			CurrentText.RemoveAt(0, 1);
		}
	}

	while (Syllables.Num() > Index)
	{
		Syllables.Pop();
	}
}

bool FLipSyncUtil::GetMorphTarget(const FString Syllable, FName& MorphTarget)
{
	const FName* Find = LipSyncMap.Find(Syllable);

	if (!Find)
	{
		return false;
	}

	MorphTarget = *Find;
	return true;
}

TArray<FName> FLipSyncUtil::GetMorphTargets()
{
	return MorphTargets;
}

bool FLipSyncUtil::ContainsSpeechPause(const FString Text, FString& Match)
{
	const FRegexPattern Pattern(SpeechPauseRegex);
	FRegexMatcher       Matcher(Pattern, Text);

	if (!Matcher.FindNext())
	{
		return false;
	}

	Match = Matcher.GetCaptureGroup(0);
	UE_LOG(LogTellMeYourSecret, Log, TEXT("Found Speech pause: %s"), *Match)
	return true;
}

bool FLipSyncUtil::Remove(FString& CurrentText, const FString Remove)
{
	if (!CurrentText.RemoveFromStart(Remove, ESearchCase::IgnoreCase))
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("Could not remove %s from %s at index 0"), *Remove, *CurrentText)
		return false;
	}
	UE_LOG(LogTellMeYourSecret, Error, TEXT("Removed %s from %s at index 0"), *Remove, *CurrentText)
	return true;
}

void FLipSyncUtil::Emplace(TArray<FSyllable>& Syllables, const int32 SyllablesIndex, FString Letters)
{
	bool bEmplace = true;

	if (Syllables.Num() > SyllablesIndex)
	{
		const FSyllable Existing = Syllables[SyllablesIndex];
		if (Existing.Syllable == Letters)
		{
			bEmplace = false;
		}
	}

	if (bEmplace)
	{
		Syllables.EmplaceAt(SyllablesIndex, Letters);
	}
}
