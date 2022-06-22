// Copyright Acinex Games 2020


#include "InteractiveObject.h"

#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"
#include "TellMeYourSecret/Components/LockComponent.h"
#include "TellMeYourSecret/GameInstances/InteractSubSystem.h"
#include "TellMeYourSecret/UMG/InteractWidget.h"
#include "TellMeYourSecret/Components/InteractComponent.h"

void AInteractiveObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	InputSettings = UInputSettings::GetInputSettings();

	GetComponents<UInteractComponent>(InteractComponents);
}

void AInteractiveObject::Use_Implementation(const FGameplayTagContainer Identity, FLatentActionInfo LatentInfo)
{
}

void AInteractiveObject::ShowTooltip()
{
	if (GetWidget() && !GetWidget()->IsInViewport())
	{
		GetWidget()->AddToViewport();
	}
}

void AInteractiveObject::HideTooltip()
{
	if (Widget && Widget->IsInViewport())
	{
		Widget->RemoveFromParent();
	}
}

bool AInteractiveObject::Interact(const FGameplayTagContainer Identity, FLatentActionInfo LatentInfo)
{
	if (bCanBeUsed && !IsLocked(Identity))
	{
		Use(Identity, LatentInfo);

		if (SubSystem)
		{
			SubSystem->Interacted(this, Identity);
		}
		
		return true;
	}

	return false;
}

bool AInteractiveObject::IsLocked(const FGameplayTagContainer Identity) const
{
	if (LockComponent && LockComponent->IsLocked(Identity))
	{
		return true;
	}

	return false;
}

void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UInteractComponent>(InteractComponents);
	LockComponent = FindComponentByClass<ULockComponent>();

	SubSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UInteractSubSystem>();

	SubSystem->Register(this);
}

FText AInteractiveObject::GetText() const
{
	if (LockComponent)
	{
		const AActor* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator();

		if (PlayerPawn)
		{
			const UCharacterComponent* CharacterComponent = PlayerPawn->FindComponentByClass<UCharacterComponent>();
			if (CharacterComponent && LockComponent->IsLocked(CharacterComponent->IdentityTags))
			{
				return NSLOCTEXT("Lock", "Locked", "Locked");
			}
		}
	}

	TArray<FInputActionKeyMapping> Mappings;
	InputSettings->GetActionMappingByName(TEXT("Interact"), Mappings);

	return FText::FormatOrdered(GetTooltipText(), Mappings[0].Key.GetDisplayName());
}

FText AInteractiveObject::GetTooltipText() const
{
	return TooltipText;
}

UInteractWidget* AInteractiveObject::GetWidget()
{
	if (Widget)
	{
		return Widget;
	}

	Widget = CreateWidget<UInteractWidget>(GetGameInstance());
	if (!Widget)
	{
		return nullptr;
	}

	Widget->SetActor(this);
	Widget->SetText(GetText());
	Widget->Initialize();

	return Widget;
}

FInteractiveObjectData AInteractiveObject::Save_Implementation()
{
	FInteractiveObjectData Record;
	Record.Name = GetName();

	{
		FMemoryWriter MemoryWriter(Record.Data, true);
		FFlowArchive Ar(MemoryWriter);
		Serialize(Ar);
	}

	if (LockComponent)
	{
		FMemoryWriter MemoryWriter(Record.Data, true);
		FFlowArchive Ar(MemoryWriter);
		LockComponent->Serialize(Ar);
	}

	return Record;
}

void AInteractiveObject::Load_Implementation(const FInteractiveObjectData& Saved)
{
	{
		FMemoryReader MemoryReader(Saved.Data, true);
		FFlowArchive Ar(MemoryReader);
		Serialize(Ar);
	}

	if (LockComponent)
	{
		FMemoryReader MemoryReader(Saved.Data, true);
		FFlowArchive Ar(MemoryReader);
		LockComponent->Serialize(Ar);
	}
}
