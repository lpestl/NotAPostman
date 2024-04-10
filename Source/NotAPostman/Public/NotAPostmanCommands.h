// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NotAPostmanStyle.h"

class FNotAPostmanCommands : public TCommands<FNotAPostmanCommands>
{
public:

	FNotAPostmanCommands()
		: TCommands<FNotAPostmanCommands>(TEXT("NotAPostman"), NSLOCTEXT("Contexts", "NotAPostman", "NotAPostman Plugin"), NAME_None, FNotAPostmanStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};