#include "NumericRelation.h"

bool FNumericRelationUtil::Check(const ENumericRelation NumericRelation, const int32 Actual, const int32 Expected)
{
    switch (NumericRelation)
    {
        case ENumericRelation::Greater_Than:
            return Actual > Expected;
        case ENumericRelation::Lower_Than:
            return Actual < Expected;;
        case ENumericRelation::Equal:
            return Actual == Expected;;
        case ENumericRelation::Greater_Than_Equal:
            return Actual >= Expected;;
        case ENumericRelation::Lower_Than_Equal:
            return Actual <= Expected;;
        default: return false;
    }
}
