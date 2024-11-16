#ifndef I_SETTING_DRAWABLE_H
#define I_SETTING_DRAWABLE_H

#include <string>
#include "imgui.h"
#include "imgui_internal.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"

class ISettingDrawable {
public:
	ISettingDrawable(const std::string& NameTab);
	virtual void DrawSetting();

	std::string NameTab = "";
};

#endif // !1
