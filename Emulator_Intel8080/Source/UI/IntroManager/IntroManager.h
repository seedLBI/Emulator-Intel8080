#ifndef INTRO_MANAGER_H
#define INTRO_MANAGER_H

#include "IconFontCppHeaders/IconsFontAwesome6.h"

#include "OpenglWindow/OpenglWindow.h"
#include "UI/Setting/ISettingObject.h"
#include "SaveSystem/SaveSystem.h"
#include "Utils/ImGui.Utils.h"



class IntroManager : public ISettingObject {
public:
	IntroManager();
	~IntroManager();

	bool IsNeedDraw();

	void DrawSetting() override;
	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;

private:
	bool flag_NeedDraw = true;
};



#endif