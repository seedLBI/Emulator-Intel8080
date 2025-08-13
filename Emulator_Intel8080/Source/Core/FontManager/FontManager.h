#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "Data/Fonts/IconsFont.h"
#include "Data/Fonts//MainFont.h"

#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"
#include "ThirdParty/ImGui/imgui_impl_glfw.h"
#include "ThirdParty/ImGui/imgui_impl_opengl3.h"

#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"

#include "Config_Compilier.h"
#include "Utils/Text/Text.h"
#include "Utils/File/File.h"
#include "Utils/ImGui/Utils.ImGui.h"



#include <string>
#include <vector>
#include <iostream>


struct FontInfo {
	std::string Name;
	std::string Path;
	std::vector<uint8_t> Data;
};

class FontManager : public ISettingObject {

public:
	FontManager();
	~FontManager();

	void SetFont(const std::string& NameFont);
	void SetSize(const int& sizeFont);


	void SetOneStepBigger();
	void SetOneStepSmaller();




	void LoadNewFont();

	std::vector<FontInfo> GetList_FontInfo();
	std::vector<std::string> GetListSizes();

	void DrawSetting() override;
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;

	// INFO: Put it after ImGui::EndFrame()
	void ReloadFont();


private:
	int Current_Scale = 21;
	static const int Min_Scale = 12;
	static const int Max_Scale = 34;

	std::vector<FontInfo> List_Fonts;


	bool NeedReloadFontSize = false;
	std::string Name_Font_Selected = "";


	ImFont* MainFont = nullptr;
	ImFont* IconsFont = nullptr;

	std::vector<uint8_t> IconsFontData;
	std::vector<uint8_t> MainFontData;

	void LoadFontFromFile(std::string Path2File);

	void LoadDefaultMainFont_fromMemory();
	void LoadIconsFont_fromMemory();


};





#endif // !FONT_MANAGER_H
