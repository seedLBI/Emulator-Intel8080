#ifndef SETTING_H
#define SETTING_H

#include "Config_Compilier.h"
#include "SaveSystem\SaveSystem.h"
#include "OpenglWindow\OpenglWindow.h"
#include "UI\FontManager\FontManager.h"
#include "UI\WindowManager\WindowManager.h"
#include "UI\Workspaces\I8080.WorkspaceManager.h"
#include "UI\ProjectManager\ProjectManager.h"
#include "UI\KeyCombination\KeyCombinationHandler.h"
#include "Notification/NotificationManager.h"
#include "Emulator/EmulationThread/EmulationThread.h"
#include "UI/Widgets/I8080.UI.CodeEditor.h"
#include "Utils\TextUtils.h"


class Setting : public SaveSystem
{
public:
	Setting(FontManager* font, WindowManager* window, I8080_WorkspaceManager* WorkspaceManager,NotificationManager* notification, EmulationThread* emulation,KeyCombinationHandler* keyCombinationHandler, ProjectManager* projectManager, Widget_CodeEditor* w_codeEditor);
	~Setting();


	void Draw();


	void Toggle();
	void Open();
	bool isOpen();

	std::string Save() override;
	void Load(const std::string& Data) override;

private:
	FontManager* font = nullptr;
	I8080_WorkspaceManager* WorkspaceManager = nullptr;
	WindowManager* window = nullptr;
	NotificationManager* notification = nullptr;
	EmulationThread* emulation = nullptr;
	KeyCombinationHandler* keyCombinationHandler = nullptr;
	ProjectManager* projectManager = nullptr;
	Widget_CodeEditor* w_codeEditor = nullptr;

	bool Popup_Open = false;



	void DrawNotificationSetting();
	void DrawEmulationSetting();
};

#endif // !SETTING_H

