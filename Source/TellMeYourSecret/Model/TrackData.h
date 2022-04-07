// Copyright Acinex Games 2020

#pragma once
#include "CoreMinimal.h"
#include "TrackData.generated.h"

USTRUCT(BlueprintType)
struct FTrackData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bLeftGuard;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bRightGuard;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Bank;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Width = 1.0F;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Thickness = 1.0F;

    friend bool operator==(const FTrackData& Lhs, const FTrackData& RHS)
    {
        return Lhs.bLeftGuard == RHS.bLeftGuard
                && Lhs.bRightGuard == RHS.bRightGuard
                && Lhs.Bank == RHS.Bank
                && Lhs.Width == RHS.Width
                && Lhs.Thickness == RHS.Thickness;
    }

    friend bool operator!=(const FTrackData& Lhs, const FTrackData& RHS)
    {
        return !(Lhs == RHS);
    }
};