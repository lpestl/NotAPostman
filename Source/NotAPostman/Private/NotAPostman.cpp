// Copyright Epic Games, Inc. All Rights Reserved.

#include "NotAPostman.h"
#include "NotAPostmanStyle.h"
#include "NotAPostmanCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Widgets/NotAPostmanLayout.h"

static const FName NotAPostmanTabName("NotAPostman");

DEFINE_LOG_CATEGORY( NotAPostmanLog );

#define LOCTEXT_NAMESPACE "FNotAPostmanModule"

void FNotAPostmanModule::StartupModule()
{
	UE_LOG( NotAPostmanLog, Log, TEXT("NotAPostmanModule => StartupModule") );

	// Init style
	FNotAPostmanStyle::Initialize();
	FNotAPostmanStyle::ReloadTextures();
	// Init UI
	FNotAPostmanLayout::Initialize();
	
	FNotAPostmanCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNotAPostmanCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNotAPostmanModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNotAPostmanModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NotAPostmanTabName, FOnSpawnTab::CreateRaw(this, &FNotAPostmanModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNotAPostmanTabTitle", "NotAPostman"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

#if IS_PROGRAM
	// Note: TThis call allows you to open a window when the program starts.
	// In plugin mode, the button in the toolbar will be responsible for opening the window.
	FNotAPostmanLayout::Get().RestoreLayout();
#endif
}

void FNotAPostmanModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);
	
	// Shutdown UI
	FNotAPostmanLayout::Shutdown();	
	// Shutdown style
	FNotAPostmanStyle::Shutdown();

	FNotAPostmanCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NotAPostmanTabName);
	
	UE_LOG( NotAPostmanLog, Log, TEXT("NotAPostmanModule => ShutdownModule") )
}

TSharedRef<SDockTab> FNotAPostmanModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNotAPostmanModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NotAPostman.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FNotAPostmanModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(NotAPostmanTabName);
}

void FNotAPostmanModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNotAPostmanCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNotAPostmanCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNotAPostmanModule, NotAPostman)