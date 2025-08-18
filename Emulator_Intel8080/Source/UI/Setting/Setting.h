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
#include "UI/Setting/ISettingObject.h"
#include "Utils\TextUtils.h"


class Setting : public SaveSystem
{
public:
	Setting();
	~Setting();

	void AddSettingObject(ISettingObject* object);

	void Draw();


	void Toggle();
	void Open();
	bool isOpen();

	std::string Save() override;
	void Load(const std::string& Data) override;

private:

	struct Tabs{
		std::string TabName;
		std::vector<ISettingObject*> setting_objects;
	};

	std::vector<Tabs> tabs;


	bool Popup_Open = false;
};

#endif // !SETTING_H

