/* 
* Copyright (c) 2021 THEIA INTERACTIVE.  All rights reserved.
*
* Website: https://widgetstudio.design
* Documentation: https://docs.widgetstudio.design
* Support: marketplace@theia.io
* Marketplace FAQ: https://marketplacehelp.epicgames.com
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WSEditorObject.generated.h"


/**
 *
 */
UCLASS()
class WIDGETSTUDIOEDITOR_API UWSEditorObject : public UObject
{
	GENERATED_BODY()

public:
	UWSEditorObject(const FObjectInitializer& ObjectInitializer);
	UWSEditorObject();

	UFUNCTION()
	void HandleStyleChanged();
};
