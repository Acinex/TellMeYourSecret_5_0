// Copyright Acinex Games 2020

#include "SetBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

void USetBlackboardValue::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent*        BlackboardComp = OwnerComp.GetBlackboardComponent();
    const FBlackboardKeySelector Key            = BlackboardKey;

    if (KeyClass == UBlackboardKeyType_Object::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Object>(Key.SelectedKeyName, Object);
    }
    if (KeyClass == UBlackboardKeyType_Class::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Class>(Key.SelectedKeyName, Class);
    }
    if (KeyClass == UBlackboardKeyType_Enum::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Enum>(Key.SelectedKeyName, Enum);
    }
    if (KeyClass == UBlackboardKeyType_Int::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Int>(Key.SelectedKeyName, Integer);
    }
    if (KeyClass == UBlackboardKeyType_Float::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Float>(Key.SelectedKeyName, Float);
    }
    if (KeyClass == UBlackboardKeyType_Bool::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Bool>(Key.SelectedKeyName, Boolean);
    }
    if (KeyClass == UBlackboardKeyType_Name::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Name>(Key.SelectedKeyName, Name);
    }
    if (KeyClass == UBlackboardKeyType_Vector::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Vector>(Key.SelectedKeyName, Vector);
    }
    if (KeyClass == UBlackboardKeyType_Rotator::StaticClass())
    {
        BlackboardComp->SetValue<UBlackboardKeyType_Rotator>(Key.SelectedKeyName, Rotator);
    }
}
