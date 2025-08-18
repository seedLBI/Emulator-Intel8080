#ifndef I_SETTING_DRAWABLE_H
#define I_SETTING_DRAWABLE_H

#include <string>
#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"
#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

class ISettingDrawable {
public:
	ISettingDrawable(const std::string& NameTab);
	virtual void DrawSetting();

	std::string NameTab = "";
};

#endif // !1
