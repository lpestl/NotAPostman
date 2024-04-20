// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NotAPostmanLayout.h"

#include "NotAPostmanCommands.h"


#define LOCTEXT_NAMESPACE "NotAPostmanLayout"

namespace NotAPostmanMenu
{
	TSharedRef< FWorkspaceItem > MenuRoot = FWorkspaceItem::NewGroup( NSLOCTEXT( "NotAPostman", "MenuRoot", "MenuRoot" ) );
	TSharedRef< FWorkspaceItem > SubTabs = MenuRoot->AddGroup( NSLOCTEXT( "NotAPostman", "SecondaryTabs", "NotAPostman sections Tabs" ) );
}

TSharedPtr< FNotAPostmanLayout > FNotAPostmanLayout::LayoutInstance = nullptr;

static TSharedPtr< FTabManager > NotAPostmanTabManager;

void FNotAPostmanLayout::Initialize()
{
	if (!LayoutInstance.IsValid())
	{
		LayoutInstance = Create();

		ensure( LayoutInstance.IsUnique() );
		LayoutInstance->RegistrTabSpawner();
	}
}

void FNotAPostmanLayout::Shutdown()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner( FName("NotAPostman") );
	FNotAPostmanCommands::Unregister();

	ensure( LayoutInstance.IsUnique() );
}

FNotAPostmanLayout& FNotAPostmanLayout::Get()
{
	return *LayoutInstance;
}

FName FNotAPostmanLayout::GetLayoutName()
{
	static FName LayoutName( TEXT( "NotAPostmanLayout" ) );
	return LayoutName;
}

TSharedPtr<FTabManager> FNotAPostmanLayout::GetTabManager()
{
	return NotAPostmanTabManager;
}

void FNotAPostmanLayout::RestoreLayout() const
{
	//FGlobalTabmanager::Get()->RestoreFrom( MainLayout.ToSharedRef(), TSharedPtr<SWindow>() );
	FGlobalTabmanager::Get()->TryInvokeTab( FName( "NotAPostmanTab" ) );
}

void FNotAPostmanLayout::DisplaySuccessNotification()
{
	// TODO:
}

void FNotAPostmanLayout::DisplayFailureNotification()
{
	// TODO:
}

void FNotAPostmanLayout::DisplayErrorMessage()
{
	// TODO:
}

void FNotAPostmanLayout::DisplayInProgressNotification(const FText& Text)
{
	// TODO:
}

void FNotAPostmanLayout::RemoveInProgressNotification()
{
	// TODO:
}

void FNotAPostmanLayout::RegistrTabSpawner()
{
	FNotAPostmanCommands::Register();

	PluginCommands = MakeShareable( new FUICommandList );
	PluginCommands->MapAction(
		FNotAPostmanCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw( this, &FNotAPostmanLayout::RestoreLayout ),
		FCanExecuteAction(),
		FIsActionChecked(),
		FIsActionButtonVisible());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNotAPostmanLayout::RegistrMenuAndButtons));
}

TSharedRef<FNotAPostmanLayout> FNotAPostmanLayout::Create()
{
	return MakeShareable( new FNotAPostmanLayout() );
}
