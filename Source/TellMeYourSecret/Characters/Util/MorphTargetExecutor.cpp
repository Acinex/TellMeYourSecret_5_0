#include "MorphTargetExecutor.h"

#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"

UMorphTargetExecutor::UMorphTargetExecutor(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UMorphTargetExecutor::AddMorphTargetChange(UCharacterComponent* CharacterComponent, const FMorphTargetChange MorphTargetChange)
{
	if (MorphTargetChange.Time == 0.0F)
	{
		CharacterComponent->GetMesh()->SetMorphTarget(MorphTargetChange.Name, MorphTargetChange.Value);
		OnStepFinished.Broadcast();
		return;
	}

	FMorphTargetExecution* TargetExecution = new FMorphTargetExecution(MorphTargetChange);

	const FTimerDelegate TimerCallback = FTimerDelegate::CreateUObject(this, &UMorphTargetExecutor::ExecuteMorphTargetChange, CharacterComponent, TargetExecution);

	GetWorld()->GetTimerManager().SetTimer(TargetExecution->TimerHandle, TimerCallback, TargetExecution->GetRate(), true, 0);
}

void UMorphTargetExecutor::Stop() const
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMorphTargetExecutor::ExecuteMorphTargetChange(UCharacterComponent* CharacterComponent, FMorphTargetExecution* TargetExecution)
{
	TargetExecution->Step();
	CharacterComponent->GetMesh()->SetMorphTarget(TargetExecution->GetName(), TargetExecution->GetCurrentValue());

	if (TargetExecution->GetCurrentValue() >= TargetExecution->GetTargetValue())
	{
		GetWorld()->GetTimerManager().ClearTimer(TargetExecution->TimerHandle);
		OnStepFinished.Broadcast();
	}
}
