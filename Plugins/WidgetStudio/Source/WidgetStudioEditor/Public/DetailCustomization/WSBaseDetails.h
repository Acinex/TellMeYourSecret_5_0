// "// Copyright (c) 2021 THEIA INTERACTIVE.  All rights reserved."

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FModernButtonDetails : public IDetailCustomization
{
public:
	// IDetailCustomization Interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance();
};