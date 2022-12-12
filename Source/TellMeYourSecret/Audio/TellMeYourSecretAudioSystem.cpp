// Copyright Acinex Games 2020


#include "TellMeYourSecretAudioSystem.h"

#include "AudioModulationStatics.h"
#include "SoundControlBus.h"
#include "SoundControlBusMix.h"
#include "TMYSAudioSettings.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

void UTellMeYourSecretAudioSystem::PostInitialize()
{
	if (const UTMYSAudioSettings* AudioSettings = GetDefault<UTMYSAudioSettings>())
	{
		if (UObject* ObjPath = AudioSettings->DefaultControlBusMix.TryLoad())
		{
			if (USoundControlBusMix* SoundControlBusMix = Cast<USoundControlBusMix>(ObjPath))
			{
				DefaultBaseMix = SoundControlBusMix;
			}
			else
			{
				ensureMsgf(SoundControlBusMix, TEXT("Default Control Bus Mix reference missing from Lyra Audio Settings."));
			}
		}

		if (UObject* ObjPath = AudioSettings->UserSettingsControlBusMix.TryLoad())
		{
			if (USoundControlBusMix* SoundControlBusMix = Cast<USoundControlBusMix>(ObjPath))
			{
				UserMix = SoundControlBusMix;
			}
			else
			{
				ensureMsgf(SoundControlBusMix, TEXT("User Control Bus Mix reference missing from Lyra Audio Settings."));
			}
		}

		if (UObject* ObjPath = AudioSettings->MainVolumeControlBus.TryLoad())
		{
			if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
			{
				MainControlBus = SoundControlBus;
			}
			else
			{
				ensureMsgf(SoundControlBus, TEXT("Overall Control Bus reference missing from Lyra Audio Settings."));
			}
		}

		if (UObject* ObjPath = AudioSettings->MusicVolumeControlBus.TryLoad())
		{
			if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
			{
				MusicControlBus = SoundControlBus;
			}
			else
			{
				ensureMsgf(SoundControlBus, TEXT("Music Control Bus reference missing from Lyra Audio Settings."));
			}
		}

		if (UObject* ObjPath = AudioSettings->SoundFXVolumeControlBus.TryLoad())
		{
			if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
			{
				SoundFXControlBus = SoundControlBus;
			}
			else
			{
				ensureMsgf(SoundControlBus, TEXT("SoundFX Control Bus reference missing from Lyra Audio Settings."));
			}
		}

		if (UObject* ObjPath = AudioSettings->DialogueVolumeControlBus.TryLoad())
		{
			if (USoundControlBus* SoundControlBus = Cast<USoundControlBus>(ObjPath))
			{
				DialogueControlBus = SoundControlBus;
			}
			else
			{
				ensureMsgf(SoundControlBus, TEXT("Dialogue Control Bus reference missing from Lyra Audio Settings."));
			}
		}
	}
}

void UTellMeYourSecretAudioSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWorldBeginPlay"))
	if (const UWorld* World = InWorld.GetWorld())
	{
		// Activate the default base mix
		if (DefaultBaseMix)
		{
			UAudioModulationStatics::ActivateBusMix(World, DefaultBaseMix);
		}

		// Retrieve the user settings
		if (const USettings* Settings = GetDefault<USettings>())
		{
			// Activate the User Mix
			if (UserMix)
			{
	UE_LOG(LogTemp, Warning, TEXT("ActivateBusMix"))
				UAudioModulationStatics::ActivateBusMix(World, UserMix);

				if (MainControlBus && MusicControlBus && SoundFXControlBus && DialogueControlBus)
				{
					const FSoundControlBusMixStage OverallControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, MainControlBus, *Settings->Volumes.Find(EVolumeType::Master));
					const FSoundControlBusMixStage MusicControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, MusicControlBus, *Settings->Volumes.Find(EVolumeType::Music));
					const FSoundControlBusMixStage SoundFXControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, SoundFXControlBus, *Settings->Volumes.Find(EVolumeType::Effects));
					const FSoundControlBusMixStage DialogueControlBusMixStage = UAudioModulationStatics::CreateBusMixStage(World, DialogueControlBus, *Settings->Volumes.Find(EVolumeType::Voice));

					TArray<FSoundControlBusMixStage> ControlBusMixStageArray;
					ControlBusMixStageArray.Add(OverallControlBusMixStage);
					ControlBusMixStageArray.Add(MusicControlBusMixStage);
					ControlBusMixStageArray.Add(SoundFXControlBusMixStage);
					ControlBusMixStageArray.Add(DialogueControlBusMixStage);

					UE_LOG(LogTemp, Warning, TEXT("UpdateMix"))
					UAudioModulationStatics::UpdateMix(World, UserMix, ControlBusMixStageArray);
				}
			}
		}
	}
}

void UTellMeYourSecretAudioSystem::ApplyOrRemoveLoadingScreenMix(bool bWantsLoadingScreenMix)
{
}
