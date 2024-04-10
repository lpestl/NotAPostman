// Copyright Epic Games, Inc. All Rights Reserved.

#include "NotAPostmanCommands.h"

#define LOCTEXT_NAMESPACE "FNotAPostmanModule"

void FNotAPostmanCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "NotAPostman", "Bring up NotAPostman window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
