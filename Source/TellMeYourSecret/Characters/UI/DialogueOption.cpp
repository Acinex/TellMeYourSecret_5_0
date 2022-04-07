#include "DialogueOption.h"

#include "Components/Button.h"
#include "Components/RichTextBlock.h"

void UDialogueOption::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    Button->OnClicked.AddDynamic(this, &UDialogueOption::Choose);
}

void UDialogueOption::SetText(const FText& InText) const
{
    Text->SetText(InText);
}

void UDialogueOption::SetDialogueContainer(UDialogueContainer* InDialogueContainer)
{
    DialogueContainer = InDialogueContainer;
}

int32 UDialogueOption::GetIndex() const
{
    return Index;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UDialogueOption::Choose()
{
    DialogueContainer->ChooseDialogueOption(Index);
}
