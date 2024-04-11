// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/NotAPostmanLayout.h"


#define LOCTEXT_NAMESPACE "NotAPostmanLayout"

TSharedPtr< FNotAPostmanLayout > FNotAPostmanLayout::LayoutInstance = nullptr;

static TSharedPtr< FTabManager > NotAPostmanTabManager;

void FNotAPostmanLayout::Initialize()
{
}

void FNotAPostmanLayout::Shutdown()
{
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
