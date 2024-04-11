#pragma once

#include "CoreMinimal.h"
#include "Framework/Docking/TabManager.h"

class FUICommandList;
class SNotificationItem;

class NOTAPOSTMAN_API FNotAPostmanLayout
{
public:
	static void Initialize();

	static void Shutdown();

	static FNotAPostmanLayout& Get();
	static FName GetLayoutName();
	TSharedPtr< FTabManager > GetTabManager();

	void RestoreLayout() const;
	
	static void DisplaySuccessNotification();
	static void DisplayFailureNotification();
	static void DisplayErrorMessage();

	void DisplayInProgressNotification(const FText& Text);
	void RemoveInProgressNotification();
	
private:
	static TSharedPtr< class FNotAPostmanLayout > LayoutInstance;
	TSharedPtr< FTabManager::FLayout > MainLayout = nullptr;
	TSharedPtr< FUICommandList > PluginCommands;
	
	TWeakPtr< SNotificationItem > OperationInProgressNotification;
};