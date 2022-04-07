#pragma once

#include "ClothSlot.generated.h"

UENUM(BlueprintType)
enum class EClothSlot: uint8
{
	Pants,
	Underpants,
	Bra,
	Socks,
	Shoes,
	Top,
	Dress,
	Hat,
	Gloves
};
