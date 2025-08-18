#ifndef INTRO_MANAGER_H
#define INTRO_MANAGER_H


#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"

#include "Utils/ImGui/Utils.ImGui.h"



class IntroManager : public ISettingObject {
public:
	IntroManager();
	~IntroManager();

	bool IsNeedDraw();

	void DrawSetting() override;
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;

private:
	bool flag_NeedDraw = true;
};



#endif