#ifndef SETTING_H
#define SETTING_H

#include "Config_Compilier.h"
#include "SaveSystem\SaveSystem.h"
#include "OpenglWindow\OpenglWindow.h"
#include "UI\FontManager\FontManager.h"
#include "UI\WindowManager\WindowManager.h"
#include "Notification/NotificationManager.h"
#include "UI/EmulationThread/EmulationThread.h"
#include "Utils\TextUtils.h"


class Setting : public SaveSystem
{
public:
	Setting(FontManager* font, WindowManager* window,NotificationManager* notification, EmulationThread* emulation);
	~Setting();


	void Draw();

	void Open();
	bool isOpen();

	std::string Save() override;
	void Load(const std::string& Data) override;

private:
	FontManager* font = nullptr;
	WindowManager* window = nullptr;
	NotificationManager* notification = nullptr;
	EmulationThread* emulation = nullptr;


	bool Popup_Open = false;
};

#endif // !SETTING_H

