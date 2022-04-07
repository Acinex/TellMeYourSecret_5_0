// Copyright Acinex Games 2020

#include "ReputationDecorator.h"


#include "TellMeYourSecret/Characters/NonPlayerCharacter.h"
#include "TellMeYourSecret/Characters/NonPlayerCharacterController.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Kismet/GameplayStatics.h"

bool UReputationDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    ANonPlayerCharacterController* NonPlayerCharacterController = Cast<ANonPlayerCharacterController>(OwnerComp.GetOwner());
    if (!NonPlayerCharacterController)
    {
        return false;
    }

    UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(OwnerComp.GetOwner());
    if (!GameInstance)
    {
        return false;
    }

    UReputationSystem* ReputationSystem = GameInstance->GetSubsystem<UReputationSystem>();
    if (!ReputationSystem)
    {
        return false;
    }

    const ANonPlayerCharacter* NonPlayerCharacter = NonPlayerCharacterController->GetNonPlayerCharacter();

    return ReputationSystem->Check(NonPlayerCharacter, NumericRelation, Reputation);
}
