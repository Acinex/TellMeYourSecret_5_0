// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "TellMeYourSecretAudioSystem.generated.h"

class USoundControlBus;
class USoundControlBusMix;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UTellMeYourSecretAudioSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void PostInitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:
	void ApplyOrRemoveLoadingScreenMix(bool bWantsLoadingScreenMix);

	// Default Sound Control Bus Mix retrieved from the Lyra Audio Settings
	UPROPERTY(Transient)
	USoundControlBusMix* DefaultBaseMix = nullptr;

	// User Sound Control Bus Mix retrieved from the Lyra Audio Settings
	UPROPERTY(Transient)
	USoundControlBusMix* UserMix = nullptr;

	// Overall Sound Control Bus retrieved from the Lyra Audio Settings and linked to the UI and game settings in LyraSettingsLocal
	UPROPERTY(Transient)
	USoundControlBus* MainControlBus = nullptr;

	// Music Sound Control Bus retrieved from the Lyra Audio Settings and linked to the UI and game settings in LyraSettingsLocal
	UPROPERTY(Transient)
	USoundControlBus* MusicControlBus = nullptr;

	// SoundFX Sound Control Bus retrieved from the Lyra Audio Settings and linked to the UI and game settings in LyraSettingsLocal
	UPROPERTY(Transient)
	USoundControlBus* SoundFXControlBus = nullptr;

	// Dialogue Sound Control Bus retrieved from the Lyra Audio Settings and linked to the UI and game settings in LyraSettingsLocal
	UPROPERTY(Transient)
	USoundControlBus* DialogueControlBus = nullptr;

	bool bAppliedLoadingScreenMix = false;
};
