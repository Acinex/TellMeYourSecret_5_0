#pragma once
#include "CoreMinimal.h"

namespace Colors
{
	const FLinearColor Pink(FColor::FromHex("#a8417d"));
	const FLinearColor White(FColor::FromHex("#fff"));
	const FLinearColor Black(FColor::FromHex("#000"));
	const FLinearColor LightBlue(FColor::FromHex("#4c99cf"));
	const FLinearColor MarinaBlue(FColor::FromHex("#4973a5"));
	const FLinearColor Purple(FColor::FromHex("#5a5387"));
	const FLinearColor Lavender(FColor::FromHex("#534367"));
	const FLinearColor Blackcurrant(FColor::FromHex("#272030"));
	const FLinearColor MidGrey(FColor::FromHex("#5d5d5d"));
	const FLinearColor DarkGrey(FColor::FromHex("#2f2f2f"));
	const FLinearColor Prelude(FColor::FromHex("#ccc0d3"));
	const FLinearColor DeepPink(FColor::FromHex("#eb1693"));
	const FLinearColor MediumVioletRed(FColor::FromHex("#bd0497"));
	const FLinearColor Transparent(0, 0, 0, 0);

	namespace Quests
	{
		const FLinearColor Done(0.009064, 0.286458, 0.017429, 1);
	}
}
