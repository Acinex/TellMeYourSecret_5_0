// Copyright Acinex Games 2020

#include "LipSyncPreview.h"

#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/Util/LipSyncExecutor.h"
#include "Kismet/GameplayStatics.h"
#include "PropertyEditor/Public/IDetailsView.h"

const FString ULipSyncPreview::SaveName = TEXT("LipSyncPreview");

void ULipSyncPreview::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UGameplayStatics::DoesSaveGameExist(SaveName, 0))
	{
		PreviewData = Cast<ULipSyncPreviewData>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));
	}
	else
	{
		PreviewData = NewObject<ULipSyncPreviewData>(this);
	}

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.bShowPropertyMatrixButton = false;
	Args.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyModule.CreateDetailView(Args);

	DetailsView->SetObject(PreviewData);

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &ULipSyncPreview::Play);
	}
}

void ULipSyncPreview::Play()
{
	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		UNonPlayerComponent* NonPlayerComponent = (*It)->FindComponentByClass<UNonPlayerComponent>();
		if (!NonPlayerComponent)
		{
			continue;
		}

		if (!NonPlayerComponent->IdentityTags.HasAllExact(PreviewData->Identity))
		{
			continue;
		}

		UGameplayStatics::SetGlobalPitchModulation(NonPlayerComponent, DilationSlider->GetValue(), 0.0F);
		UGameplayStatics::SetGlobalTimeDilation(NonPlayerComponent, DilationSlider->GetValue());

		Executor = NewObject<ULipSyncExecutor>(NonPlayerComponent, TEXT("Executor"));
		Executor->Start(NonPlayerComponent, {
			                PreviewData->Audio,
			                PreviewData->AudioDelay,
			                PreviewData->Syllables,
			                PreviewData->LipSyncDelay,
			                PreviewData->Montage,
			                PreviewData->StartSectionName
		                });
	}

	UGameplayStatics::SaveGameToSlot(PreviewData, SaveName, 0);
}
